#include "PCH.h"
#include "ApplicationException.h"

void ThrowLastErrorInfo(LPCWSTR fallback, ...)
{
	CComPtr<IErrorInfo> error;
	CComBSTR msg;

	GetErrorInfo(0, &error);

	if (!error || FAILED(error->GetDescription(&msg)))
	{
		CString formatted;
		va_list args;

		va_start(args, fallback);
		try
		{
			formatted.FormatV(fallback, args);
		}
		catch (...)
		{
			ATLTRY(va_end(args));
			throw;
		}
		va_end(args);

		msg = formatted;
	}

	throw CApplicationException(L"%s", BSTR(msg));
}

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
