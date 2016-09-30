#include "PCH.h"
#include "MainWindow.h"

CMainWindow *g_pMainWindow;

// {1EE63CD2-F159-45B5-A87C-5AB0946DB9BE}
static CONST GUID g_MainTrayIconId = { 0x1ee63cd2, 0xf159, 0x45b5, { 0xa8, 0x7c, 0x5a, 0xb0, 0x94, 0x6d, 0xb9, 0xbe } };

////////////////////////////////////////////////////////////////////////////////
// Constructors & Destructors.

CMainWindow::CMainWindow()
{
	if (!m_mainTrayMenu.LoadMenu(IDR_MAINTRAYMENU))
		AtlThrowLastWin32();
}

////////////////////////////////////////////////////////////////////////////////
// CMessageFilter Implementation.

BOOL CMainWindow::PreTranslateMessage(MSG * /* pMsg */)
{
	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////
// Message Handlers.

VOID CMainWindow::OnActivate(UINT nState, BOOL /* bMinimized */, CWindow /* wndOther */)
{
	switch (nState)
	{
	case WA_INACTIVE:
		ShowWindow(SW_HIDE);
		break;
	}
}

INT CMainWindow::OnCreate(LPCREATESTRUCT /* lpCreateStruct */)
{
	InitializeWindowPosition();

	m_pMainTrayIcon.Attach(new CTrayIcon(*this, g_MainTrayIconId));
	m_pMainTrayIcon->Create(0U, APP_NAME, WM_MAINTRAYICON);

	try
	{
		if (!_Module.GetMessageLoop()->AddMessageFilter(this))
		{
			ATLTRY(m_pMainTrayIcon->Destroy());
			return -1;
		}
	}
	catch (...)
	{
		ATLTRY(m_pMainTrayIcon->Destroy());
		return -1;
	}

	return 0;
}

VOID CMainWindow::OnDestroy()
{
	// It is OK to be fail since message loop will be already stopped before we destroy this instance.
	// Message loop will never access this instance after it stopped.
	_Module.GetMessageLoop()->RemoveMessageFilter(this);

	PostQuitMessage(EXIT_TYPE_NORMAL);
}

VOID CMainWindow::OnExit(UINT /* uNotifyCode */, int /* nID */, CWindow /* wndCtl */)
{
	m_pMainTrayIcon->Destroy();

	if (!DestroyWindow())
		MessageBox(L"Failed to destroy main window. Please terminate program manually from Task Manager.", APP_NAME, MB_OK | MB_ICONHAND);
}

LRESULT CMainWindow::OnMainTrayIcon(UINT /* uMsg */, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(lParam))
	{
	case WM_LBUTTONUP:
		ShowWindow(SW_SHOW);
		SetForegroundWindow(*this);
		break;
	case WM_CONTEXTMENU:
		ShowMainTrayIconMenu(GET_X_LPARAM(wParam), GET_Y_LPARAM(wParam));
		break;
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
// Helper Functions.

VOID CMainWindow::InitializeWindowPosition()
{
	CRect rcWorkArea;
	if (!SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0))
		AtlThrowLastWin32();

	CRect rcWindow;

	rcWindow.left = rcWorkArea.right - 1000;
	rcWindow.top = rcWorkArea.bottom - 500;
	rcWindow.right = rcWorkArea.right;
	rcWindow.bottom = rcWorkArea.bottom;

	SetWindowPos(NULL, rcWindow, SWP_NOACTIVATE | SWP_NOZORDER);
}

VOID CMainWindow::ShowMainTrayIconMenu(INT nX, INT nY)
{
	// The window that own the notification icon must be the foreground window before we show a popup menu.
	// Otherwise the popup menu will not disappear when it lost focus.
	if (!SetForegroundWindow(*this) || !TrackPopupMenuEx(m_mainTrayMenu.GetSubMenu(0), 0, nX, nY, *this, NULL))
		AtlThrowLastWin32();
}
