#include "PCH.h"
#include "EngineProperties.h"

CEngineProperties::CEngineProperties(CAutoPtr<CEngineConfig> pConfig, const CPath& EngineDir) :
	m_pConfig(pConfig),
	m_EngineDir(EngineDir)
{
}

const CEngineConfig& CEngineProperties::GetConfig() const
{
	return *m_pConfig;
}

const CPath& CEngineProperties::GetEngineDirectory() const
{
	return m_EngineDir;
}
