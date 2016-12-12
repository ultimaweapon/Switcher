#include "PCH.h"
#include "Error.h"

std::wstring com_last_error(const wchar_t * fallback, ...)
{
	CComPtr<IErrorInfo> e;
	CComBSTR msg;

	GetErrorInfo(0, &e);

	if (!e || FAILED(e->GetDescription(&msg)))
	{
		CString fmt;
		va_list args;

		va_start(args, fallback);
		try
		{
			fmt.FormatV(fallback, args);
		}
		catch (...)
		{
			va_end(args);
			throw;
		}
		va_end(args);

		msg = fmt;
	}

	return msg.m_str;
}
