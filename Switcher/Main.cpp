#include "PCH.h"
#include "Configurations.h"

static VOID RunWTL(HINSTANCE hInstance, INT nCmdShow)
{
	HRESULT hr;

	hr = _Module.Init(NULL, hInstance);
	if (FAILED(hr))
		AtlThrow(hr);

	_Module.Term();
}

EXTERN_C INT CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE /* hPrevInstance */, LPWSTR /* lpCmdLine */, INT nCmdShow)
{
	HRESULT hr;

	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"CoInitializeEx() failed. Please contact developer.", APP_NAME, MB_OK | MB_ICONHAND);
		return hr;
	}

	try
	{
		RunWTL(hInstance, nCmdShow);
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

	CoUninitialize();

	return hr;
}
