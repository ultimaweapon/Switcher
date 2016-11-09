#pragma once

class CApplicationException
{
public:
	CApplicationException(LPCWSTR pszFormat, ...);
	CApplicationException(HRESULT hr, LPCWSTR pszFormat, ...);
public:
	HRESULT GetErrorCode() const;
	const CString& GetMessage() const;
private:
	CString m_strMessage;
	HRESULT m_hr;
};
