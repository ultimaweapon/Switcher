#include "PCH.h"
#include "Configurations.h"
#include "MainWindow.h"
#include "TrayIcon.h"

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

static VOID Run()
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
