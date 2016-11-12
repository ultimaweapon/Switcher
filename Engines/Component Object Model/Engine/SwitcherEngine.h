#pragma once

#include "COM.h"

class ATL_NO_VTABLE SwitcherEngine :
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<SwitcherEngine, &CLSID_SwitcherEngine>,
	public ISwitcherEngine
{
public:
	DECLARE_NO_REGISTRY()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(SwitcherEngine)
		COM_INTERFACE_ENTRY(ISwitcherEngine)
	END_COM_MAP()
protected:
	SwitcherEngine();
	~SwitcherEngine();
private:
	SwitcherEngine(const SwitcherEngine&) {}
	SwitcherEngine& operator=(const SwitcherEngine&) {};
};
