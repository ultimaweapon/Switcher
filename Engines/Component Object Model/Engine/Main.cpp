#include "PCH.h"

#include "SwitcherEngine.h"

#include "COM.h"
#include "COM_i.c"

BEGIN_OBJECT_MAP(g_ComClasses)
	OBJECT_ENTRY(__uuidof(SwitcherEngine), SwitcherEngine)
END_OBJECT_MAP()

HRESULT __stdcall DllCanUnloadNow()
{
	return _Module.DllCanUnloadNow();
}

HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
	return _Module.DllGetClassObject(rclsid, riid, ppv);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID /* lpvReserved */)
{
	static BOOL blInitialized;
	HRESULT hr;

	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		hr = _Module.Init(g_ComClasses, hinstDLL, &LIBID_COMEngine);
		if (FAILED(hr))
			return FALSE;
		blInitialized = TRUE;
		break;
	case DLL_PROCESS_DETACH:
		if (blInitialized)
			_Module.Term();
		break;
	}

	return TRUE;
}
