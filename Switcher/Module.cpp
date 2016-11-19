#include "PCH.h"
#include "Module.h"

CSwitcherModule::CSwitcherModule() : m_pszModule(NULL), m_pszModuleDir(NULL)
{
}

CSwitcherModule::~CSwitcherModule()
{
	ATLTRY(free(m_pszModuleDir));
	ATLTRY(delete[] m_pszModule);
}

LPCWSTR CSwitcherModule::GetModuleDirectory() const
{
	return m_pszModuleDir;
}

LPCWSTR CSwitcherModule::GetModulePath() const
{
	return m_pszModule;
}

HRESULT CSwitcherModule::Init(_ATL_OBJMAP_ENTRY *pObjMap, HINSTANCE hInstance, const GUID *pLibID)
{
	HRESULT hr = CServerAppModule::Init(pObjMap, hInstance, pLibID);
	if (FAILED(hr))
		return hr;

	try
	{
		InitializeModule();
	}
	catch (CAtlException& e)
	{
		ATLTRY(CServerAppModule::Term());
		return e;
	}
	catch (...)
	{
		ATLTRY(CServerAppModule::Term());
		throw;
	}

	return hr;
}

VOID CSwitcherModule::InitializeModule()
{
	InitializeModuleDetails();
}

VOID CSwitcherModule::InitializeModuleDetails()
{
	// Get full path of the module.
	DWORD dwBuffer = MAX_PATH / 2, dwCopied;

	do
	{
		delete[] m_pszModule; m_pszModule = NULL;
		m_pszModule = new WCHAR[dwBuffer *= 2];

		dwCopied = GetModuleFileName(GetModuleInstance(), m_pszModule, dwBuffer);
		if (!dwCopied)
			AtlThrowLastWin32();
	} while (dwCopied == dwBuffer);

	// Get path of directory that contains the module.
	m_pszModuleDir = _wcsdup(m_pszModule);
	if (!m_pszModuleDir)
		AtlThrow(E_OUTOFMEMORY);

	ATLPath::RemoveFileSpec(m_pszModuleDir);
}
