#pragma once

#include "COM.h"

class ATL_NO_VTABLE SwitcherEngine :
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<SwitcherEngine, &CLSID_SwitcherEngine>,
	public ISwitchEngine
{
public:
	DECLARE_NO_REGISTRY()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(SwitcherEngine)
		COM_INTERFACE_ENTRY(ISwitchEngine)
	END_COM_MAP()
public:
	HRESULT FinalConstruct();
public:
	virtual HRESULT STDMETHODCALLTYPE Config(HWND switcher);
	virtual HRESULT STDMETHODCALLTYPE GetCapabilities(ENGINE_CAPABILITIES *result);
	virtual HRESULT STDMETHODCALLTYPE LoadSwitchType(ISwitchTypeProperties *props, ISwitchType **result);
protected:
	SwitcherEngine();
	~SwitcherEngine();
private:
	HRESULT SetError(HRESULT hr, LPCWSTR pszFormat, ...);
	HRESULT SetError(REFIID InterfaceId, HRESULT hr, LPCWSTR pszFormat, va_list FormatArgs);
	HRESULT SetSwitchEngineError(HRESULT hr, LPCWSTR pszFormat, ...);
private:
	CString m_strEngineName;
private:
	SwitcherEngine(const SwitcherEngine&) {}
	SwitcherEngine& operator=(const SwitcherEngine&) {};
};
