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
	virtual HRESULT STDMETHODCALLTYPE Config(HWND switcher);
	virtual HRESULT STDMETHODCALLTYPE IsConfigurable(BOOL *result);
	virtual HRESULT STDMETHODCALLTYPE LoadAllSwitchTypes(SAFEARRAY **result);
protected:
	SwitcherEngine();
	~SwitcherEngine();
private:
	SwitcherEngine(const SwitcherEngine&) {}
	SwitcherEngine& operator=(const SwitcherEngine&) {};
};
