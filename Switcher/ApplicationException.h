#pragma once

class CApplicationException
{
public:
	CApplicationException(const CString& strMessage);
public:
	const CString& GetMessage() const;
private:
	CString m_strMessage;
};
