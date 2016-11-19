#pragma once

#include "Engine_h.h"

class ATL_NO_VTABLE SwitchTypeConfig :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<SwitchTypeConfig>,
	public ISwitchTypeConfig
{
public:
	SwitchTypeConfig(const SwitchTypeConfig&) = delete;

	DECLARE_NO_REGISTRY()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(SwitchTypeConfig)
		COM_INTERFACE_ENTRY(ISwitchTypeConfig)
	END_COM_MAP()

	SwitchTypeConfig& operator=(const SwitchTypeConfig&) = delete;

	const GUID& GetEngineId() const;
	const GUID& GetSwitchTypeId() const;
	VOID SetEngineId(const GUID& Id);
	VOID SetSwitchTypeId(const GUID& Id);

	virtual HRESULT STDMETHODCALLTYPE get_EngineId(GUID *result);
	virtual HRESULT STDMETHODCALLTYPE get_SwitchId(GUID *result);
protected:
	SwitchTypeConfig();
	~SwitchTypeConfig();
private:
	GUID sid;
	GUID eid;
};
