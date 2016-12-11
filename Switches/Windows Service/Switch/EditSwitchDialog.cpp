#include "PCH.h"
#include "EditSwitchDialog.h"

CEditSwitchDialog::CEditSwitchDialog() :
	swt(nullptr)
{
}

BOOL CEditSwitchDialog::OnInitDialog(CWindow /* wndFocus */, LPARAM lInitParam)
{
	swt = reinterpret_cast<Switch *>(lInitParam);

	_ASSERTE(swt);

	return FALSE; // Don't allow system to set focus on wndFocus.
}
