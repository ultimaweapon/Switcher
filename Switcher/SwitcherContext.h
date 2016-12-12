#pragma once

class CMainWindow;
class loaded_switch_type;

typedef std::unordered_map<GUID, std::shared_ptr<loaded_switch_type>> switch_type_map;

class switcher_context final
{
public:
	const CMainWindow * get_main_window() const;
	const switch_type_map * get_switch_types() const;
	void set_main_window(const std::weak_ptr<CMainWindow>& wnd);
	void set_switch_types(const std::weak_ptr<switch_type_map>& p);
private:
	std::weak_ptr<CMainWindow> mainwnd;
	std::weak_ptr<switch_type_map> stypes;
};
