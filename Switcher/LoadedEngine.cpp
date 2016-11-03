#include "PCH.h"
#include "LoadedEngine.h"

CLoadedEngine::CLoadedEngine(CAutoPtr<CEngineProperties> pProps, const CComPtr<ISwitcherEngine>& pEngine) :
	m_pProps(pProps),
	m_pEngine(pEngine)
{
}
