#pragma once

#include "EngineProperties.h"

#include "Engine_h.h"

class CLoadedEngine
{
public:
	CLoadedEngine(CAutoPtr<CEngineProperties> pProps, const CComPtr<ISwitcherEngine>& pEngine);
private:
	CAutoPtr<CEngineProperties> m_pProps;
	CComPtr<ISwitcherEngine> m_pEngine;
private:
	CLoadedEngine(const CLoadedEngine&) {};
	CLoadedEngine& operator=(const CLoadedEngine&) {};
};
