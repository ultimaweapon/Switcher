#pragma once

#include "EngineConfig.h"

class CEngineProperties
{
public:
	CEngineProperties(CAutoPtr<CEngineConfig> pConfig, const CString& strEngineName, const CPath& EngineDir);
public:
	const CEngineConfig& GetConfig() const;
	const CPath& GetEngineDirectory() const;
	const CString& GetEngineName() const;
private:
	CAutoPtr<CEngineConfig> m_pConfig;
	CString m_strEngineName;
	CPath m_EngineDir;
private:
	CEngineProperties(const CEngineProperties&) {};
	CEngineProperties& operator=(const CEngineProperties&) {};
};
