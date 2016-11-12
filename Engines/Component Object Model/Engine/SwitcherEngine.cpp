#include "PCH.h"
#include "SwitcherEngine.h"

SwitcherEngine::SwitcherEngine()
{
}

SwitcherEngine::~SwitcherEngine()
{
}

HRESULT SwitcherEngine::Config(HWND switcher)
{
	return E_NOTIMPL;
}

HRESULT SwitcherEngine::IsConfigurable(BOOL *result)
{
	if (!result) return E_POINTER;
	*result = FALSE;
	return S_OK;
}

HRESULT SwitcherEngine::LoadAllSwitchTypes(SAFEARRAY **result)
{
	return E_NOTIMPL;
}
