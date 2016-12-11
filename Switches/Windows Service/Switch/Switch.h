#pragma once

#include "Engine.h"

class ATL_NO_VTABLE Switch :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<Switch>,
	public ISwitch
{
public:
	Switch(const Switch&) = delete;

	DECLARE_NO_REGISTRY()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(Switch)
		COM_INTERFACE_ENTRY(ISwitch)
	END_COM_MAP()

	Switch& operator=(const Switch&) = delete;
protected:
	Switch();
	~Switch();
};
