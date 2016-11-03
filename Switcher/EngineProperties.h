#pragma once

#include "EngineConfig.h"

class CEngineProperties
{
public:
	CEngineProperties(CAutoPtr<CEngineConfig> pConfig, const CPath& EngineDir);
public:
	const CEngineConfig& GetConfig() const;
	const CPath& GetEngineDirectory() const;
private:
	CAutoPtr<CEngineConfig> m_pConfig;
	CPath m_EngineDir;
private:
	CEngineProperties(const CEngineProperties&) {};
	CEngineProperties& operator=(const CEngineProperties&) {};
};
