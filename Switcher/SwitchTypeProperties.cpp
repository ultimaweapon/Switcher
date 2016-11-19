#include "PCH.h"
#include "SwitchTypeProperties.h"

SwitchTypeProperties::SwitchTypeProperties()
{
}

SwitchTypeProperties::~SwitchTypeProperties()
{
}

const SwitchTypeConfig * SwitchTypeProperties::GetConfig() const
{
	return conf;
}

LPCWSTR SwitchTypeProperties::GetDirectory() const
{
	return dir.c_str();
}

LPCWSTR SwitchTypeProperties::GetName() const
{
	return name.c_str();
}

VOID SwitchTypeProperties::SetConfig(SwitchTypeConfig *pConfig)
{
	conf = pConfig;
}

VOID SwitchTypeProperties::SetDirectory(LPCWSTR pszDirectory)
{
	dir = pszDirectory;
}

VOID SwitchTypeProperties::SetName(LPCWSTR pszName)
{
	name = pszName;
}

HRESULT SwitchTypeProperties::get_Config(ISwitchTypeConfig **result)
{
	if (!result) return E_POINTER;
	return conf.QueryInterface(result);
}

HRESULT SwitchTypeProperties::get_Directory(BSTR *result)
{
	if (!result) return E_POINTER;
	*result = SysAllocString(dir.c_str());
	return S_OK;
}

HRESULT SwitchTypeProperties::get_Name(BSTR *result)
{
	if (!result) return E_POINTER;
	*result = SysAllocString(name.c_str());
	return S_OK;
}
