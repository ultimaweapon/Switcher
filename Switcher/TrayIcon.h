#pragma once

class CTrayIcon
{
public:
	CTrayIcon(CWindow& owner, REFGUID id);
	CTrayIcon(const CTrayIcon&) = delete;
public:
	CTrayIcon& operator=(const CTrayIcon&) = delete;
public:
	VOID Create(_U_STRINGorID icon, PCWSTR pszTip, UINT uMessageId);
	VOID Destroy();
private:
	NOTIFYICONDATA m_iconData;
	CWindow& m_owner;
};
