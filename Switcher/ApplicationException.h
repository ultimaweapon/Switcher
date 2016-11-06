#pragma once

class CApplicationException
{
public:
	CApplicationException(LPCWSTR pszFormat, ...);
public:
	const CString& GetMessage() const;
private:
	CString m_strMessage;
};
