#pragma once

#include "Switch_h.h"

class ATL_NO_VTABLE SwitchType :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<SwitchType, &CLSID_SwitchType>,
	public ISwitchBuilder,
	public ISwitchType
{
public:
	SwitchType(const SwitchType&) = delete;

	DECLARE_NO_REGISTRY()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(SwitchType)
		COM_INTERFACE_ENTRY(ISwitchBuilder)
		COM_INTERFACE_ENTRY(ISwitchType)
	END_COM_MAP()

	SwitchType& operator=(const SwitchType&) = delete;

	// ISwitchBuilder Implementation.
	HRESULT STDMETHODCALLTYPE NewSwitch(HWND switcher, ISwitch **result) override;

	// ISwitchType Implementation.
	HRESULT STDMETHODCALLTYPE Initialize(HWND switcher) override;
protected:
	SwitchType();
	~SwitchType();
};
