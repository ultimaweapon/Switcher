#pragma once

#include "Configurations.h"
#include "Resources.h"
#include "TrayIcon.h"
#include "WindowMessages.h"

enum EXIT_TYPE
{
	EXIT_TYPE_NORMAL
};

typedef CWinTraits<WS_BORDER | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP, WS_EX_COMPOSITED | WS_EX_TOOLWINDOW> CMainWindowTraits;

class CMainWindow :
	public CWindowImpl<CMainWindow, CWindow, CMainWindowTraits>,
	public CMessageFilter
{
public: // Constructors & Destructors.
	CMainWindow();
public: // ATL & WTL Properties.
	DECLARE_WND_CLASS_EX(APP_NAME, CS_DBLCLKS | CS_NOCLOSE, COLOR_WINDOW)

	BEGIN_MSG_MAP(CMainWindow)
		MESSAGE_HANDLER_EX(WM_MAINTRAYICON, OnMainTrayIcon)
		MSG_WM_ACTIVATE(OnActivate)
		COMMAND_ID_HANDLER_EX(ID_MENU_EXIT, OnExit)
		MSG_WM_DESTROY(OnDestroy)
		MSG_WM_CREATE(OnCreate)
	END_MSG_MAP()
public: // CMessageFilter Implementation.
	virtual BOOL PreTranslateMessage(MSG *pMsg);
private: // Message Handlers.
	VOID OnActivate(UINT nState, BOOL bMinimized, CWindow wndOther);
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	VOID OnDestroy();
	VOID OnExit(UINT uNotifyCode, int nID, CWindow wndCtl);
	LRESULT OnMainTrayIcon(UINT uMsg, WPARAM wParam, LPARAM lParam);
private: // Helper Functions.
	VOID InitializeWindowPosition();
	VOID ShowMainTrayIconMenu(INT nX, INT nY);
private: // Variables.
	CAutoPtr<CTrayIcon> m_pMainTrayIcon;
	CMenu m_mainTrayMenu;
};

extern CMainWindow *g_pMainWindow;
