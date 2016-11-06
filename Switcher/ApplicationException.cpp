#include "PCH.h"
#include "ApplicationException.h"

CApplicationException::CApplicationException(LPCWSTR pszFormat, ...)
{
	va_list ArgList;

	va_start(ArgList, pszFormat);
	try
	{
		m_strMessage.FormatV(pszFormat, ArgList);
	}
	catch (...)
	{
		va_end(ArgList);
		throw;
	}
	va_end(ArgList);
}

const CString& CApplicationException::GetMessage() const
{
	return m_strMessage;
}
