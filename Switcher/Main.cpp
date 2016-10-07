#include "PCH.h"

#include "Configurations.h"
#include "EngineConfig.h"
#include "FileUtility.h"
#include "MainWindow.h"
#include "TrayIcon.h"

static BOOL LoadEngine(LPCWSTR pszDir, const WIN32_FIND_DATA *pFileDetails, LPVOID pContext)
{
	HRESULT hr;

	if (!(pFileDetails->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		return TRUE;

	CPath EngineDir = pszDir;
	if (!EngineDir.Append(pFileDetails->cFileName))
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

	// Construct CEngineConfig.
	CAutoPtr<CEngineConfig> pConfig(new CEngineConfig(EngineId, szEngineManifest));

	return TRUE;
}

static VOID LoadEngines()
{
	// Construct the path of directory that contains engines.
	CPath EnginesDir = _Module.GetModuleDirectory();
	if (!EnginesDir.Append(ENGINES_DIRECTORY))
		AtlThrow(E_UNEXPECTED);

	// List all engines.
	EnumerateFiles(EnginesDir, LoadEngine, NULL);
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
	LoadEngines();
	RunMainWindow();
}

static VOID RunWTL(HINSTANCE hInstance)
{
	HRESULT hr;

	hr = _Module.Init(NULL, hInstance);
	if (FAILED(hr))
		AtlThrow(hr);

	__try
	{
		Run();
	}
	__finally
	{
		_Module.Term();
	}
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
		RunWTL(hInstance);
		hr = S_OK;
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
