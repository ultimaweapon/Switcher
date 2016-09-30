#pragma once

class CSwitcherModule : public CAppModule
{
public:
	CSwitcherModule();
	~CSwitcherModule();
public:
	LPCWSTR GetModuleDirectory() const;
	LPCWSTR GetModulePath() const;
	HRESULT Init(_ATL_OBJMAP_ENTRY *pObjMap, HINSTANCE hInstance, const GUID *pLibID = NULL);
private:
	VOID InitializeModule();
	VOID InitializeModuleDetails();
private:
	LPWSTR m_pszModule;
	LPWSTR m_pszModuleDir;
};
