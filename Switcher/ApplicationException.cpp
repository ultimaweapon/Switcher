#include "PCH.h"
#include "ApplicationException.h"

CApplicationException::CApplicationException(LPCWSTR pszFormat, ...) :
	m_hr(E_FAIL)
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

CApplicationException::CApplicationException(HRESULT hr, LPCWSTR pszFormat, ...) :
	m_hr(hr)
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

HRESULT CApplicationException::GetErrorCode() const
{
	return m_hr;
}

const CString& CApplicationException::GetMessage() const
{
	return m_strMessage;
}
