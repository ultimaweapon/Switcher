#pragma once

#include "EngineProperties.h"

#include "Engine_h.h"

class CLoadedEngine
{
public:
	CLoadedEngine(CAutoPtr<CEngineProperties> pProps, const CComPtr<ISwitchEngine>& pEngine);
private:
	CAutoPtr<CEngineProperties> m_pProps;
	CComPtr<ISwitchEngine> m_pEngine;
private:
	CLoadedEngine(const CLoadedEngine&) {};
	CLoadedEngine& operator=(const CLoadedEngine&) {};
};
