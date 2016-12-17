#include "PCH.h"
#include "ActionPanel.h"

#include "Error.h"
#include "LoadedSwitchType.h"
#include "MainWindow.h"

////////////////////////////////////////////////////////////////////////////////
// Initializer/Finalizer.

CActionPanel::CActionPanel() :
	ctx(nullptr)
{
}

////////////////////////////////////////////////////////////////////////////////
// Event Handlers.

void CActionPanel::OnConfigureSwitchType(
	const std::shared_ptr<CMenu>& /* pMenu */,
	const CComPtr<ISwitchTypeConfigurator>& pConfigurator,
	SwitchTypeProperties *pProps)
{
	_ASSERTE(pConfigurator);
	_ASSERTE(pProps);

	auto hr = pConfigurator->ConfigureSwitchType(ctx->get_main_window()->m_hWnd);
	if (FAILED(hr))
	{
		auto m = com_last_error(L"Failed to configure switch %s: 0x%X.", pProps->GetName(), hr);
		MessageBox(m.c_str(), APP_NAME, MB_ICONHAND | MB_OK);
		return;
	}
}

int CActionPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	ctx = reinterpret_cast<const switcher_context *>(lpCreateStruct->lpCreateParams);

	_ASSERTE(ctx);

	CreateSwitchesMenu();
	CreateSwitchesButton();

	return 0;
}

void CActionPanel::OnNewSwitch(const std::shared_ptr<CMenu>& /* pMenu */, const CComPtr<ISwitchBuilder>& pBuilder)
{
	CComPtr<ISwitch> s;
	auto hr = pBuilder->NewSwitch(ctx->get_main_window()->m_hWnd, &s);
	if (FAILED(hr))
	{
		auto m = com_last_error(L"Failed to create new switch: 0x%X.", hr);
		MessageBox(m.c_str(), APP_NAME, MB_ICONHAND | MB_OK);
		return;
	}
}

void CActionPanel::OnSwitchesClicked(UINT /* uNotifyCode */, int /* nID */, CWindow /* wndCtl */)
{
	// Get coordinate to show menu.
	CRect p;
	if (!sb.GetWindowRect(p))
		AtlThrowLastWin32();

	// Show Menu.
	int id = TrackPopupMenu(
		sc,
		TPM_RIGHTALIGN | TPM_BOTTOMALIGN | TPM_NONOTIFY | TPM_RETURNCMD | TPM_LEFTBUTTON | TPM_VERNEGANIMATION,
		p.right,
		p.top,
		0,
		*this,
		nullptr);

	if (!id)
		return;

	// Execute Handler.
	auto it = sh.find(id);
	if (it == sh.end())
		return;

	it->second();
}

////////////////////////////////////////////////////////////////////////////////
// Helper.

CMenu& CActionPanel::CreateSwitchMenu(
	SwitchTypeProperties *pProps,
	ISwitchBuilder *pBuilder,
	ISwitchTypeConfigurator *pConfigurator)
{
	_ASSERTE(pProps);

	// Every menu item must hold a reference to this object to prevent it destroyed.
	auto m = std::make_shared<CMenu>();
	if (!m->CreatePopupMenu())
		AtlThrowLastWin32();

	// New Switch.
	if (pBuilder)
	{
		auto h = std::bind(&CActionPanel::OnNewSwitch, this, m, pBuilder);
		int id;

		do
		{
			id = std::rand();
		} while (!sh.insert(std::make_pair(id, h)).second);

		if (!m->AppendMenu(MF_ENABLED | MF_STRING | MF_UNCHECKED, id, L"New Switch..."))
			AtlThrowLastWin32();
	}

	// Options.
	if (pConfigurator)
	{
		auto h = std::bind(&CActionPanel::OnConfigureSwitchType, this, m, pConfigurator, pProps);
		int id;

		do
		{
			id = std::rand();
		} while (!sh.insert(std::make_pair(id, h)).second);

		if (!m->AppendMenu(MF_SEPARATOR))
			AtlThrowLastWin32();

		if (!m->AppendMenu(MF_ENABLED | MF_STRING | MF_UNCHECKED, id, L"Options..."))
			AtlThrowLastWin32();
	}

	return *m;
}

VOID CActionPanel::CreateSwitchesButton()
{
	CRect rc(5, 5, 80, 28);

	if (!sb.Create(*this, rc, L"Switches", WS_CHILD | WS_VISIBLE, 0, COMMAND_SWITCHES_MENU))
		AtlThrowLastWin32();
}

VOID CActionPanel::CreateSwitchesMenu()
{
	// Sort Switch Types.
	auto st = ctx->get_switch_types();

	std::vector<loaded_switch_type *> ost;
	ost.reserve(st->size());

	std::transform(st->cbegin(), st->cend(), std::back_inserter(ost), [](const switch_type_map::value_type& e)
	{
		return e.second.get();
	});

	std::sort(ost.begin(), ost.end(), [](loaded_switch_type *v1, loaded_switch_type *v2)
	{
		return wcscmp(v1->properties()->GetName(), v2->properties()->GetName()) < 0;
	});

	// Create Menu Items.
	CreateSwitchesMenu(ost);
}

VOID CActionPanel::CreateSwitchesMenu(const std::vector<loaded_switch_type*>& SwitchTypes)
{
	// Create the menu itselft.
	if (!sc.CreatePopupMenu())
		AtlThrowLastWin32();

	// Create menu item for each switch type.
	for (auto st : SwitchTypes)
	{
		UINT f = MF_STRING | MF_UNCHECKED;

		// Determine actions that switch type is supported.
		CComPtr<ISwitchBuilder> sb;
		auto hsb = SUCCEEDED(st->switch_type()->QueryInterface(&sb));

		CComPtr<ISwitchTypeConfigurator> stc;
		auto hstc = SUCCEEDED(st->switch_type()->QueryInterface(&stc));

		if (hsb || hstc)
		{
			// Switch type has actions.
			auto& m = CreateSwitchMenu(
				st->properties(),
				hsb ? sb : nullptr,
				hstc ? stc : nullptr);

			if (!sc.AppendMenu(f | MF_ENABLED | MF_POPUP, m, st->properties()->GetName()))
				AtlThrowLastWin32();
		}
		else
		{
			// Switch type does not support any actions.
			if (!sc.AppendMenu(f | MF_GRAYED, UINT_PTR(0), st->properties()->GetName()))
				AtlThrowLastWin32();
		}
	}
}
