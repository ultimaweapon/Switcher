#include "PCH.h"
#include "TrayIcon.h"

CTrayIcon::CTrayIcon(CWindow& owner, REFGUID id) : m_owner(owner)
{
	ZeroMemory(&m_iconData, sizeof(m_iconData));

	m_iconData.cbSize = sizeof(m_iconData);
	m_iconData.hWnd = owner;
	m_iconData.uFlags = NIF_GUID;
	m_iconData.guidItem = id;
}

VOID CTrayIcon::Create(_U_STRINGorID icon, PCWSTR pszTip, UINT uMessageId)
{
	ATLASSERT(pszTip);

	m_iconData.uFlags |= NIF_MESSAGE | NIF_ICON | NIF_TIP;
	m_iconData.uCallbackMessage = uMessageId;
	m_iconData.hIcon = AtlLoadIconImage(icon);
	wcscpy_s(m_iconData.szTip, pszTip);

	if (!Shell_NotifyIcon(NIM_ADD, &m_iconData))
		AtlThrow(E_UNEXPECTED);
}

VOID CTrayIcon::Destroy()
{
	if (!Shell_NotifyIcon(NIM_DELETE, &m_iconData))
		AtlThrow(E_UNEXPECTED);
}
