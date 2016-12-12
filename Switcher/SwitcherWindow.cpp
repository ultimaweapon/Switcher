#include "PCH.h"
#include "SwitcherWindow.h"

CSwitcherWindow::CSwitcherWindow(HWND hWnd) noexcept :
	CWindow(hWnd)
{
}

HWND CSwitcherWindow::Create(
	LPCTSTR lpstrWndClass,
	HWND hWndParent,
	_U_RECT rect,
	LPCTSTR szWindowName,
	DWORD dwStyle,
	DWORD dwExStyle,
	_U_MENUorID MenuOrID,
	LPVOID lpCreateParam)
{
	auto h = CWindow::Create(lpstrWndClass, hWndParent, rect, szWindowName, dwStyle, dwExStyle, MenuOrID, lpCreateParam);
	if (!h)
		return h;

	auto font = AtlGetStockFont(DEFAULT_GUI_FONT);
	if (!font)
		AtlThrow(E_UNEXPECTED);

	SetFont(font);

	return h;
}
