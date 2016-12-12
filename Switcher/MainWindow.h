#pragma once

#include "ActionPanel.h"
#include "Configurations.h"
#include "Resources.h"
#include "SwitcherContext.h"
#include "SwitcherWindow.h"
#include "TrayIcon.h"
#include "WindowMessages.h"

enum EXIT_TYPE
{
	EXIT_TYPE_NORMAL
};

typedef CWinTraits<WS_BORDER | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP, WS_EX_COMPOSITED | WS_EX_TOOLWINDOW> CMainWindowTraits;

class CMainWindow :
	public CWindowImpl<CMainWindow, CSwitcherWindow, CMainWindowTraits>,
	public CMessageFilter
{
public: // Constructors & Destructors.
	CMainWindow();
public: // ATL & WTL Properties.
	DECLARE_WND_CLASS_EX(APP_NAME, CS_DBLCLKS | CS_NOCLOSE, COLOR_WINDOW)

	BEGIN_MSG_MAP(CMainWindow)
		MSG_WM_ACTIVATEAPP(OnActivateApp)
		MESSAGE_HANDLER_EX(WM_MAINTRAYICON, OnMainTrayIcon)
		COMMAND_ID_HANDLER_EX(ID_MENU_EXIT, OnExit)
		MSG_WM_DESTROY(OnDestroy)
		MSG_WM_CREATE(OnCreate)
	END_MSG_MAP()
public: // CMessageFilter Implementation.
	virtual BOOL PreTranslateMessage(MSG *pMsg);
private: // Message Handlers.
	void OnActivateApp(BOOL bActive, DWORD dwThreadID);
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	VOID OnDestroy();
	VOID OnExit(UINT uNotifyCode, int nID, CWindow wndCtl);
	LRESULT OnMainTrayIcon(UINT uMsg, WPARAM wParam, LPARAM lParam);
private: // Helper Functions.
	VOID CreateActionPanel();
	VOID CreateSplitter();
	VOID InitializeWindowPosition();
	VOID ShowMainTrayIconMenu(INT nX, INT nY);

	const switcher_context *ctx;
	CAutoPtr<CTrayIcon> m_pMainTrayIcon;
	CMenu m_mainTrayMenu;
	CStatic splt;
	CActionPanel actpanel;
};
