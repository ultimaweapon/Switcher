#include "PCH.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID /* lpvReserved */)
{
	static BOOL blInitialized;
	HRESULT hr;

	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		hr = _Module.Init(NULL, hinstDLL);
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
