#include "PCH.h"
#include "LoadedEngine.h"

CLoadedEngine::CLoadedEngine(CAutoPtr<CEngineConfig> pConfig, const CComPtr<ISwitcherEngine>& pEngine) :
	m_pConfig(pConfig),
	m_pEngine(pEngine)
{
}
