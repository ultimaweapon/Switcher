#pragma once

#include "PlatformTarget.h"

// Windows Headers:

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

// ATL & WTL Headers:

#define _ATL_APARTMENT_THREADED
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define _WTL_NO_WTYPES
#define _WTL_NO_CSTRING

#include <atlbase.h>
#include <atltypes.h>
#include <atlstr.h>
#include <atlapp.h>

extern CAppModule _Module;

#include <atlmisc.h>
