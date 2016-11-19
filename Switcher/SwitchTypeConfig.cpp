#include "PCH.h"
#include "SwitchTypeConfig.h"

SwitchTypeConfig::SwitchTypeConfig() :
	sid(GUID_NULL),
	eid(GUID_NULL)
{
}

SwitchTypeConfig::~SwitchTypeConfig()
{
}

const GUID& SwitchTypeConfig::GetEngineId() const
{
	return eid;
}

const GUID& SwitchTypeConfig::GetSwitchTypeId() const
{
	return sid;
}

VOID SwitchTypeConfig::SetEngineId(const GUID& Id)
{
	eid = Id;
}

VOID SwitchTypeConfig::SetSwitchTypeId(const GUID& Id)
{
	sid = Id;
}

HRESULT SwitchTypeConfig::get_EngineId(GUID *result)
{
	if (!result) return E_POINTER;
	*result = eid;
	return S_OK;
}

HRESULT SwitchTypeConfig::get_SwitchId(GUID *result)
{
	if (!result) return E_POINTER;
	*result = sid;
	return S_OK;
}
