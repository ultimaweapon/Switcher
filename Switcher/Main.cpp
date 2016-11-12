#include "PCH.h"

#include "ApplicationException.h"
#include "Configurations.h"
#include "EngineConfig.h"
#include "EngineProperties.h"
#include "FileUtility.h"
#include "GlobalRef.h"
#include "LoadedEngine.h"
#include "LoadedEngines.h"
#include "MainWindow.h"
#include "TrayIcon.h"

#include "Engine_h.h"

static VOID RaiseEngineManifestActivationError(HRESULT hr, LPCWSTR pszEngineName, LPCWSTR pszManifestFile, LPCWSTR lpManifestResName)
{
	if (!lpManifestResName)
		throw CApplicationException(hr, L"Failed to activate manifest %s for engine %s: 0x%X", pszManifestFile, pszEngineName, hr);
	else if (IS_INTRESOURCE(lpManifestResName))
		throw CApplicationException(hr, L"Failed to activate manifest %u inside %s for engine %s: 0x%X", lpManifestResName, pszManifestFile, pszEngineName, hr);
	else
		throw CApplicationException(hr, L"Failed to activate manifest %s inside %s for engine %s: 0x%X", lpManifestResName, pszManifestFile, pszEngineName, hr);
}

static CComPtr<ISwitchEngine> InstantiateEngine(const CEngineProperties& EngineProps)
{
	const CEngineConfig& Config = EngineProps.GetConfig();
	HRESULT hr;
	HANDLE hActCtx;
	ULONG_PTR uActCookie;
	CComPtr<ISwitchEngine> pEngine;

	// Activate Activation Context.
	const CString& strManifest = EngineProps.GetConfig().GetManifestFile();
	if (!strManifest.IsEmpty())
	{
		ACTCTX Params = { 0 };

		Params.cbSize = sizeof(Params);
		Params.dwFlags = ACTCTX_FLAG_ASSEMBLY_DIRECTORY_VALID;
		Params.lpSource = strManifest;
		Params.lpAssemblyDirectory = EngineProps.GetEngineDirectory();

		LPCWSTR lpManifestResName = Config.GetManifestResourceName();
		if (lpManifestResName)
		{
			Params.lpResourceName = lpManifestResName;
			Params.dwFlags |= ACTCTX_FLAG_RESOURCE_NAME_VALID;
		}

		hActCtx = CreateActCtx(&Params);
		if (hActCtx == INVALID_HANDLE_VALUE)
		{
			hr = AtlHresultFromLastError();
			RaiseEngineManifestActivationError(hr, EngineProps.GetEngineName(), strManifest, lpManifestResName);
		}

		try
		{
			if (!ActivateActCtx(hActCtx, &uActCookie))
			{
				hr = AtlHresultFromLastError();
				RaiseEngineManifestActivationError(hr, EngineProps.GetEngineName(), strManifest, lpManifestResName);
			}
		}
		catch (...)
		{
			ATLTRY(ReleaseActCtx(hActCtx));
			throw;
		}
	}
	else
	{
		hActCtx = INVALID_HANDLE_VALUE;
		uActCookie = 0;
	}

	// Instantiate ISwitcherEngine.
	try
	{
		hr = pEngine.CoCreateInstance(Config.GetEngineId(), NULL, CLSCTX_INPROC_SERVER);
		if (FAILED(hr))
			throw CApplicationException(hr, L"Failed to create ISwitcherEngine instance for engine %s: 0x%X", EngineProps.GetEngineName().GetString(), hr);
	}
	catch (...)
	{
		if (hActCtx != INVALID_HANDLE_VALUE)
		{
			try
			{
				if (DeactivateActCtx(0, uActCookie))
					ReleaseActCtx(hActCtx);
			}
			catch (...)
			{
				// Swallow.
			}
		}
		throw;
	}

	if (hActCtx != INVALID_HANDLE_VALUE)
	{
		if (!DeactivateActCtx(0, uActCookie))
		{
			hr = AtlHresultFromLastError();
			throw CApplicationException(hr, L"Failed to deactivate manifest for engine %s: 0x%X.", EngineProps.GetEngineName().GetString(), hr);
		}
		ReleaseActCtx(hActCtx);
	}

	return pEngine;
}

static BOOL LoadEngine(LPCWSTR pszDir, const WIN32_FIND_DATA *pFileDetails, LPVOID pContext)
{
	CEngineList *pEngineList = reinterpret_cast<CEngineList *>(pContext);
	HRESULT hr;

	if (!(pFileDetails->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		return TRUE;

	LPCWSTR pszEngineName = pFileDetails->cFileName;

	CPath EngineDir = pszDir;
	if (!EngineDir.Append(pszEngineName))
		AtlThrow(E_UNEXPECTED);

	// Read Engine.ini.
	CPath ConfigFile = EngineDir;
	if (!ConfigFile.Append(L"Engine.ini"))
		AtlThrow(E_UNEXPECTED);

	WCHAR szEngineId[64];
	GetPrivateProfileString(L"Engine", L"ID", NULL, szEngineId, _countof(szEngineId), ConfigFile);

	GUID EngineId;
	hr = IIDFromString(szEngineId, &EngineId);
	if (FAILED(hr))
		AtlThrow(hr);

	WCHAR szEngineManifest[MAX_PATH];
	GetPrivateProfileString(L"Engine", L"Manifest", NULL, szEngineManifest, _countof(szEngineManifest), ConfigFile);

	WCHAR szManifestResId[8];
	GetPrivateProfileString(L"Engine", L"ManifestResourceID", NULL, szManifestResId, _countof(szManifestResId), ConfigFile);

	LPCWSTR pszManifestResName;

	if (szManifestResId[0])
	{
		ULONG_PTR uResId = wcstoul(szManifestResId, NULL, 0);
		pszManifestResName = reinterpret_cast<LPCWSTR>(uResId);
		if (!pszManifestResName || !IS_INTRESOURCE(pszManifestResName))
			throw CApplicationException(L"Invalid ManifestResourceID in Engine.ini of %s engine.", pszEngineName);
	}
	else
	{
		WCHAR szManifestResName[256];
		GetPrivateProfileString(L"Engine", L"ManifestResourceName", NULL, szManifestResName, _countof(szManifestResName), ConfigFile);
		pszManifestResName = szManifestResName[0] ? szManifestResName : NULL;
	}

	// Instantiate Engine Properties.
	CAutoPtr<CEngineConfig> pConfig(new CEngineConfig(EngineId, szEngineManifest, pszManifestResName));
	CAutoPtr<CEngineProperties> pEngineProps(new CEngineProperties(pConfig, pszEngineName, EngineDir));

	// Instantiate Engine.
	CAutoPtr<CLoadedEngine> pLoaded(new CLoadedEngine(pEngineProps, InstantiateEngine(*pEngineProps)));
	pEngineList->AddTail(pLoaded);

	return TRUE;
}

static CAutoPtr<CEngineList> LoadEngines()
{
	// Construct the path of directory that contains engines.
	CPath EnginesDir = _Module.GetModuleDirectory();
	if (!EnginesDir.Append(ENGINES_DIRECTORY))
		AtlThrow(E_UNEXPECTED);

	// List all engines.
	CAutoPtr<CEngineList> pEngines(new CEngineList());
	EnumerateFiles(EnginesDir, LoadEngine, pEngines);

	if (pEngines->GetCount() == 0)
		throw CApplicationException(L"There is no any engines installed. Please install at least one engine before using " APP_NAME ".");

	return pEngines;
}

static VOID CreateMainWindow()
{
	ATLASSERT(g_pMainWindow == NULL);

	g_pMainWindow = new CMainWindow();

	try
	{
		if (!g_pMainWindow->Create(NULL))
			AtlThrowLastWin32();
	}
	catch (...)
	{
		delete g_pMainWindow; g_pMainWindow = NULL;
		throw;
	}
}

static VOID RunMainWindow()
{
	CMessageLoop messageLoop;

	if (!_Module.AddMessageLoop(&messageLoop))
		AtlThrow(E_UNEXPECTED);

	try
	{
		// Initialize.
		CreateMainWindow();

		// Enter main loop.
		// Don't destroy main window in case of exception since we don't known it is in good state or not.
		EXIT_TYPE nExitType;
		nExitType = static_cast<EXIT_TYPE>(messageLoop.Run());

		// Clean up.
		delete g_pMainWindow; g_pMainWindow = NULL;
	}
	catch (...)
	{
		_Module.RemoveMessageLoop();
		throw;
	}

	if (!_Module.RemoveMessageLoop())
		AtlThrow(E_UNEXPECTED);
}

static VOID Run()
{
	CGlobalRef<CEngineList> pEngines(g_pEngines);
	
	pEngines = LoadEngines().Detach();
	
	RunMainWindow();
}

static HRESULT RunWTL(HINSTANCE hInstance)
{
	HRESULT hr;

	hr = _Module.Init(NULL, hInstance);
	if (FAILED(hr))
		AtlThrow(hr);

	try
	{
		Run();
		hr = S_OK;
	}
	catch (CApplicationException& e)
	{
		MessageBox(NULL, e.GetMessage(), APP_NAME, MB_OK | MB_ICONHAND);
		hr = e.GetErrorCode();
	}
	catch (...)
	{
		_Module.Term();
		throw;
	}

	_Module.Term();

	return hr;
}

EXTERN_C INT CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE /* hPrevInstance */, LPWSTR /* lpCmdLine */, INT /* nCmdShow */)
{
	HRESULT hr;

	// Turn on memory leak reporting for debug build.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Initialize COM.
	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"CoInitializeEx() failed. Please contact developer.", APP_NAME, MB_OK | MB_ICONHAND);
		return hr;
	}

	// Run Application.
	try
	{
		hr = RunWTL(hInstance);
	}
	catch (CAtlException& e)
	{
		MessageBox(NULL, L"Unexpected error occurred on ATL or WTL. Please contact developer.", APP_NAME, MB_OK | MB_ICONHAND);
		hr = e;
	}
	catch (...)
	{
		CoUninitialize();
		throw;
	}

	// Clean up.
	CoUninitialize();

	return hr;
}
