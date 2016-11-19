#pragma once

#include "PlatformTarget.h"

// Compilation Flags:

#define WIN32_LEAN_AND_MEAN

// Windows Headers:

#include <windows.h>
#include <shellapi.h>

// CRT Headers:

#include <crtdbg.h>

// C++ Headers:

#include <experimental/filesystem>
#include <unordered_map>

// ATL & WTL Headers:

#include <atlbase.h>
#include <atltypes.h>
#include <atlstr.h>
#include <atlapp.h>
#include "Module.h"

extern CSwitcherModule _Module;

#include <atlpath.h>
#include <atlcoll.h>
#include <atlwin.h>
#include <atlmisc.h>
#include <atlcrack.h>

#if _ATL_VER < 0x0700
#error This project need ATL 7.0 or higher.
#endif

// Utilities:

template<>
struct std::hash<GUID> : public std::unary_function<const GUID&, size_t>
{
	size_t operator()(const GUID& g) const
	{
		auto p = reinterpret_cast<const std::uint32_t *>(&g);
		return p[0] ^ p[1] ^ p[2] ^ p[3];
	}
};

template<class T>
CComPtr<T> CreateComObject()
{
	CComObject<T> *obj;
	auto hr = CComObject<T>::CreateInstance(&obj);
	if (FAILED(hr))
		AtlThrow(hr);

	return obj;
}
