#pragma once

class ATL_NO_VTABLE CSwitcherWindow : public CWindow
{
public:
	CSwitcherWindow(HWND hWnd = NULL) noexcept;

	HWND Create(
		LPCTSTR lpstrWndClass,
		HWND hWndParent,
		_U_RECT rect = nullptr,
		LPCTSTR szWindowName = nullptr,
		DWORD dwStyle = 0,
		DWORD dwExStyle = 0,
		_U_MENUorID MenuOrID = 0U,
		LPVOID lpCreateParam = nullptr);
};
