#pragma once

#include "SwitchTypeProperties.h"
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
	void OnConfigureSwitchType(
		const std::shared_ptr<CMenu>& pMenu,
		const CComPtr<ISwitchTypeConfigurator>& pConfigurator,
		SwitchTypeProperties *pProps);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnNewSwitch(const std::shared_ptr<CMenu>& pMenu, const CComPtr<ISwitchBuilder>& pBuilder);
	void OnSwitchesClicked(UINT uNotifyCode, int nID, CWindow wndCtl);

	// Helper.
	CMenu& CreateSwitchMenu(SwitchTypeProperties *pProps, ISwitchBuilder *pBuilder, ISwitchTypeConfigurator *pConfigurator);
	void CreateSwitchMenuItem(
		CMenu& Menu,
		LPCWSTR pszText,
		const std::function<void()>& Handler,
		UINT uFlags = MF_ENABLED | MF_STRING | MF_UNCHECKED);
	VOID CreateSwitchesButton();
	VOID CreateSwitchesMenu();
	VOID CreateSwitchesMenu(const std::vector<loaded_switch_type *>& SwitchTypes);
	int GenerateSwitchesMenuId();

	// Objects.
	const switcher_context *ctx;
	CButtonT<CSwitcherWindow> sb;
	CMenu sm;
	int smcid;
	std::unordered_map<int, std::function<void()>> sh;
};
