#pragma once

#include "SwitcherContext.h"
#include "SwitcherWindow.h"

#include "Engine_h.h"

class CActionPanel final : public CWindowImpl<CActionPanel, CSwitcherWindow>
{
public:
	// Types.
	enum COMMAND
	{
		COMMAND_SWITCHES_MENU = 1
	};

	// Initializer/Finalizer.
	CActionPanel();
	CActionPanel(const CActionPanel&) = delete;

	// ATL & WTL Properties.
	DECLARE_WND_CLASS(L"Switcher Action Panel")

	BEGIN_MSG_MAP(CActionPanel)
		COMMAND_HANDLER_EX(COMMAND_SWITCHES_MENU, BN_CLICKED, OnSwitchesClicked)
		MSG_WM_CREATE(OnCreate)
	END_MSG_MAP()

	// Operators.
	CActionPanel& operator=(const CActionPanel&) = delete;
private:
	// Event Handlers.
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnNewSwitch(std::shared_ptr<CMenu> pMenu, CComPtr<ISwitchBuilder> pBuilder);
	void OnSwitchesClicked(UINT uNotifyCode, int nID, CWindow wndCtl);

	// Helper.
	CMenu& CreateSwitchMenu(ISwitchBuilder *pBuilder);
	VOID CreateSwitchesButton();
	VOID CreateSwitchesMenu();
	VOID CreateSwitchesMenu(const std::vector<loaded_switch_type *>& SwitchTypes);

	// Objects.
	const switcher_context *ctx;
	CButtonT<CSwitcherWindow> sb;
	CMenu sc;
	std::unordered_map<int, std::function<void()>> sh;
};
