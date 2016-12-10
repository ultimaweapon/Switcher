#include "PCH.h"

#include "SwitchType.h"

#include "Switch_h.h"
#include "Switch_i.c"

BEGIN_OBJECT_MAP(coclasses)
	OBJECT_ENTRY(__uuidof(SwitchType), SwitchType)
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
	static bool init;
	HRESULT hr;

	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		hr = _Module.Init(coclasses, hinstDLL, &LIBID_WindowsServiceSwitch);
		if (FAILED(hr))
			return FALSE;
		init = true;
		break;
	case DLL_PROCESS_DETACH:
		if (!init)
			break;
		_Module.Term();
		break;
	}

	return TRUE;
}
