#include "PCH.h"
#include "EngineConfig.h"

CEngineConfig::CEngineConfig(REFGUID EngineId, LPCWSTR pszManifestFile) :
	m_EngineId(EngineId),
	m_strManifestFile(pszManifestFile)
{
}

REFGUID CEngineConfig::GetEngineId() const
{
	return m_EngineId;
}

const CString& CEngineConfig::GetManifestFile() const
{
	return m_strManifestFile;
}
