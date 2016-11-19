#pragma once

#include "EngineProperties.h"

#include "Engine_h.h"

class CLoadedEngine
{
public:
	CLoadedEngine(CAutoPtr<CEngineProperties> pProps, const CComPtr<ISwitchEngine>& pEngine);
public:
	ISwitchEngine * GetEngine();
	const CEngineProperties& GetEngineProperties() const;
private:
	CAutoPtr<CEngineProperties> m_pProps;
	CComPtr<ISwitchEngine> m_pEngine;
private:
	CLoadedEngine(const CLoadedEngine&) {};
	CLoadedEngine& operator=(const CLoadedEngine&) {};
};

typedef CMapToAutoPtr<GUID, CLoadedEngine> CEngineMap;

extern CEngineMap *g_pEngines;
