#include "PCH.h"
#include "LoadedEngine.h"

CLoadedEngine::CLoadedEngine(CAutoPtr<CEngineProperties> pProps, const CComPtr<ISwitchEngine>& pEngine) :
	m_pProps(pProps),
	m_pEngine(pEngine)
{
}
