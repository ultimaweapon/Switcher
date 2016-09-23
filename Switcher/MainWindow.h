#pragma once

#include "Configurations.h"
#include "TrayIcon.h"
#include "WindowMessages.h"

enum EXIT_TYPE
{
	EXIT_TYPE_NORMAL
};

enum MAIN_TRAY_MENU
{
	MAIN_TRAY_MENU_EXIT = 100
};

class CMainWindow :
	public CWindowImpl<CMainWindow, CWindow, CFrameWinTraits>,
	public CMessageFilter
{
public: // ATL & WTL Properties.
	DECLARE_WND_CLASS_EX(APP_NAME, CS_DBLCLKS | CS_NOCLOSE | CS_OWNDC, COLOR_WINDOW)

	BEGIN_MSG_MAP(CMainWindow)
		MESSAGE_HANDLER_EX(WM_MAINTRAYICON, OnMainTrayIcon)
		COMMAND_ID_HANDLER_EX(MAIN_TRAY_MENU_EXIT, OnExit)
		MSG_WM_DESTROY(OnDestroy)
		MSG_WM_CREATE(OnCreate)
	END_MSG_MAP()
public: // CMessageFilter Implementation.
	virtual BOOL PreTranslateMessage(MSG *pMsg);
private: // Message Handlers.
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	VOID OnDestroy();
	VOID OnExit(UINT uNotifyCode, int nID, CWindow wndCtl);
	LRESULT OnMainTrayIcon(UINT uMsg, WPARAM wParam, LPARAM lParam);
private: // Helper Functions.
private: // Variables.
	CAutoPtr<CTrayIcon> m_pMainTrayIcon;
};

extern CMainWindow *g_pMainWindow;
