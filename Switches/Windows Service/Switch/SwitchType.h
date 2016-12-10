#pragma once

#include "Switch_h.h"

class ATL_NO_VTABLE SwitchType :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<SwitchType, &CLSID_SwitchType>,
	public ISwitchType
{
public:
	SwitchType(const SwitchType&) = delete;

	DECLARE_NO_REGISTRY()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(SwitchType)
		COM_INTERFACE_ENTRY(ISwitchType)
	END_COM_MAP()

	SwitchType& operator=(const SwitchType&) = delete;
protected:
	SwitchType();
	~SwitchType();
};