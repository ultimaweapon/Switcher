#include "PCH.h"
#include "SwitcherContext.h"

const CMainWindow * switcher_context::get_main_window() const
{
	return mainwnd.lock().get();
}

const switch_type_map * switcher_context::get_switch_types() const
{
	return stypes.lock().get();
}

void switcher_context::set_main_window(const std::weak_ptr<CMainWindow>& wnd)
{
	mainwnd = wnd;
}

void switcher_context::set_switch_types(const std::weak_ptr<switch_type_map>& p)
{
	stypes = p;
}
