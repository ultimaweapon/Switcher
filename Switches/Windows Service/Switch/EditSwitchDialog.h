#pragma once

#include "Resource.h"
#include "Switch.h"

class CEditSwitchDialog final : public CDialogImpl<CEditSwitchDialog>
{
public:
	CEditSwitchDialog();
	CEditSwitchDialog(const CEditSwitchDialog&) = delete;

	enum { IDD = IDD_EDITSWITCH };

	BEGIN_MSG_MAP(CEditSwitchDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
	END_MSG_MAP()

	CEditSwitchDialog& operator=(const CEditSwitchDialog&) = delete;
private:
	BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);

	Switch *swt;
};
