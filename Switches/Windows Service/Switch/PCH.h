#pragma once

// Build Configurations:

#include "PlatformTarget.h"

#define WIN32_LEAN_AND_MEAN

// Windows Headers:

#include <windows.h>

// ATL & WTL Headers:

#include <atlbase.h>
#include <atltypes.h>
#include <atlstr.h>
#include <atlapp.h>

extern CServerAppModule _Module;

#include <atlmisc.h>
#include <atlcrack.h>

// Utility:

template<class T>
CComPtr<T> CreateComObject()
{
	CComObject<T> *obj;
	auto hr = CComObject<T>::CreateInstance(&obj);
	if (FAILED(hr))
		AtlThrow(hr);
	return obj;
}
