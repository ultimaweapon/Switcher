#include "PCH.h"
#include "EngineConfig.h"

CEngineConfig::CEngineConfig(REFGUID EngineId, LPCWSTR pszManifestFile, LPCWSTR lpManifestResName) :
	m_EngineId(EngineId),
	m_strManifestFile(pszManifestFile)
{
	if (lpManifestResName)
	{
		m_lpManifestResName = IS_INTRESOURCE(lpManifestResName) ? const_cast<LPWSTR>(lpManifestResName) : _wcsdup(lpManifestResName);
		if (!m_lpManifestResName)
			AtlThrow(E_OUTOFMEMORY);
	}
	else
		m_lpManifestResName = NULL;
}

CEngineConfig::~CEngineConfig()
{
	if (m_lpManifestResName && !IS_INTRESOURCE(m_lpManifestResName))
		free(m_lpManifestResName);
}

REFGUID CEngineConfig::GetEngineId() const
{
	return m_EngineId;
}

const CString& CEngineConfig::GetManifestFile() const
{
	return m_strManifestFile;
}

LPCWSTR CEngineConfig::GetManifestResourceName() const
{
	return m_lpManifestResName;
}
