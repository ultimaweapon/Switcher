#include "PCH.h"
#include "ApplicationException.h"

CApplicationException::CApplicationException(const CString& strMessage) :
	m_strMessage(strMessage)
{
}

const CString& CApplicationException::GetMessage() const
{
	return m_strMessage;
}
