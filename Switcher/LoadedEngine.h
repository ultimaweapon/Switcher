#pragma once

#include "EngineConfig.h"

#include "Engine_h.h"

class CLoadedEngine
{
public:
	CLoadedEngine(CAutoPtr<CEngineConfig> pConfig, const CComPtr<ISwitcherEngine>& pEngine);
private:
	CAutoPtr<CEngineConfig> m_pConfig;
	CComPtr<ISwitcherEngine> m_pEngine;
};
