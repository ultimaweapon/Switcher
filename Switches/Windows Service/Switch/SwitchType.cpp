#include "PCH.h"
#include "SwitchType.h"

#include "EditSwitchDialog.h"
#include "Switch.h"

SwitchType::SwitchType()
{
}

SwitchType::~SwitchType()
{
}

HRESULT SwitchType::NewSwitch(HWND switcher, ISwitch **result)
{
	if (!result)
		return E_POINTER;

	try
	{
		// Create Switch.
		auto swt = CreateComObject<Switch>();

		// Edit Switch.
		CEditSwitchDialog editdlg;

		if (editdlg.DoModal(switcher, reinterpret_cast<LPARAM>(swt.p)) != IDOK)
			return S_FALSE;

		return swt.QueryInterface(result);
	}
	catch (...)
	{
		return E_UNEXPECTED;
	}
}

////////////////////////////////////////////////////////////////////////////////
// ISwitchType Implementation.

HRESULT SwitchType::Initialize(HWND /* switcher */)
{
	return S_OK;
}
