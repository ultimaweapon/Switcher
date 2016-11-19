#include "PCH.h"
#include "LoadedEngine.h"

CEngineMap *g_pEngines;

CLoadedEngine::CLoadedEngine(CAutoPtr<CEngineProperties> pProps, const CComPtr<ISwitchEngine>& pEngine) :
	m_pProps(pProps),
	m_pEngine(pEngine)
{
}

ISwitchEngine * CLoadedEngine::GetEngine()
{
	return m_pEngine;
}

const CEngineProperties& CLoadedEngine::GetEngineProperties() const
{
	ATLASSERT(m_pProps);
	return *m_pProps;
}
