#pragma once

#include "PlatformTarget.h"

// Compilation Flags:

#define WIN32_LEAN_AND_MEAN

// Windows Headers:

#include <windows.h>
#include <shellapi.h>

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

// CRT Headers:

#include <crtdbg.h>
