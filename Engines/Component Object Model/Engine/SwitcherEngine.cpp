#include "PCH.h"
#include "SwitcherEngine.h"

SwitcherEngine::SwitcherEngine()
{
}

SwitcherEngine::~SwitcherEngine()
{
}

HRESULT SwitcherEngine::FinalConstruct()
{
	HRESULT hr;

	try
	{
		CPath ModuleDir;
		DWORD dwResult, dwBufsize = MAX_PATH / 2;

		do
		{
			dwBufsize *= 2;
			dwResult = GetModuleFileName(_Module.GetModuleInstance(), ModuleDir.m_strPath.GetBufferSetLength(dwBufsize), dwBufsize);
			if (!dwResult)
			{
				hr = AtlHresultFromLastError();
				return SetError(hr, L"Failed to get file name of the module: 0x%X.", hr);
			}
		} while (dwResult == dwBufsize);

		ModuleDir.m_strPath.ReleaseBuffer();

		if (!ModuleDir.RemoveFileSpec())
			return SetError(E_FAIL, L"Failed to remove file spec from the file name of the module.");

		ModuleDir.RemoveBackslash();

		m_strEngineName = ATLPath::FindFileName(ModuleDir);
	}
	catch (...)
	{
		return SetError(E_FAIL, L"Unhandled exception occurred.");
	}

	return S_OK;
}

HRESULT SwitcherEngine::Config(HWND /* switcher */)
{
	return E_NOTIMPL;
}

HRESULT SwitcherEngine::GetCapabilities(ENGINE_CAPABILITIES *result)
{
	if (!result) return E_POINTER;
	*result = ENGINE_CAPABILITY_DEFAULT;
	return S_OK;
}

HRESULT SwitcherEngine::LoadSwitchType(ISwitchTypeProperties *props, ISwitchType **result)
{
	HRESULT hr;

	if (!result)
		return E_POINTER;

	try
	{
		// Query switch properties.
		CComBSTR strSwitchName;
		hr = props->get_Name(&strSwitchName);
		if (FAILED(hr))
			return SetSwitchEngineError(hr, L"Failed to get switch name: 0x%X.", hr);

		CComBSTR strSwitchDir;
		hr = props->get_Directory(&strSwitchDir);
		if (FAILED(hr))
			return SetSwitchEngineError(hr, L"Failed to get directory for switch %s: 0x%X.", BSTR(strSwitchName), hr);

		CComPtr<ISwitchTypeConfig> pSwitchConfig;
		hr = props->get_Config(&pSwitchConfig);
		if (FAILED(hr))
			return SetSwitchEngineError(hr, L"Failed to get configuration for switch %s: 0x%X.", BSTR(strSwitchName), hr);

		GUID SwitchId;
		hr = pSwitchConfig->get_SwitchId(&SwitchId);
		if (FAILED(hr))
			return SetSwitchEngineError(hr, L"Failed to get ID for switch %s: 0x%X.", BSTR(strSwitchName), hr);

		// Load engine configurations for switch.
		CPath SwitchConfig(strSwitchDir);
		if (!SwitchConfig.Append(L"Switch.ini"))
			return SetSwitchEngineError(E_FAIL, L"Failed to construct a path to Switch.ini for switch %s: 0x%X.", BSTR(strSwitchName), hr);

		WCHAR szSwitchManifest[MAX_PATH];
		LPCWSTR lpSwitchManifestResName;

		GetPrivateProfileString(L"Engine", L"SwitchManifest", NULL, szSwitchManifest, _countof(szSwitchManifest), SwitchConfig);

		if (szSwitchManifest[0])
		{
			WCHAR szManifestName[256];
			GetPrivateProfileString(L"Engine", L"SwitchManifestResourceName", NULL, szManifestName, _countof(szManifestName), SwitchConfig);
			if (szManifestName[0])
				lpSwitchManifestResName = szManifestName;
			else
			{
				WCHAR szManifestId[8];
				GetPrivateProfileString(L"Engine", L"SwitchManifestResourceID", NULL, szManifestId, _countof(szManifestId), SwitchConfig);
				if (szManifestId[0])
				{
					unsigned long uResId = wcstoul(szManifestId, NULL, 0);
					if (!uResId || uResId > USHRT_MAX)
						return SetSwitchEngineError(E_FAIL, L"File %s has invalid value for SwitchManifestResourceID.", LPCWSTR(SwitchConfig));
					lpSwitchManifestResName = MAKEINTRESOURCE(uResId);
				}
				else
					lpSwitchManifestResName = NULL;
			}
		}
		else
			lpSwitchManifestResName = NULL;

		// Activate Activation Context.
		HANDLE hActivationCtx;
		ULONG_PTR uActivatedActCtx;

		if (szSwitchManifest[0])
		{
			CPath ManifestFile(strSwitchDir);
			if (!ManifestFile.Append(szSwitchManifest))
				return SetSwitchEngineError(E_FAIL, L"Failed to construct the path to %s for switch %s.", szSwitchManifest, BSTR(strSwitchName));

			ACTCTX ActivationCtx = { 0 };

			ActivationCtx.cbSize = sizeof(ActivationCtx);
			ActivationCtx.dwFlags = ACTCTX_FLAG_ASSEMBLY_DIRECTORY_VALID;
			ActivationCtx.lpSource = ManifestFile;
			ActivationCtx.lpAssemblyDirectory = strSwitchDir;

			if (lpSwitchManifestResName)
			{
				ActivationCtx.dwFlags |= ACTCTX_FLAG_RESOURCE_NAME_VALID;
				ActivationCtx.lpResourceName = lpSwitchManifestResName;
			}

			hActivationCtx = CreateActCtx(&ActivationCtx);
			if (hActivationCtx == INVALID_HANDLE_VALUE)
			{
				hr = AtlHresultFromLastError();
				return SetSwitchEngineError(hr, L"Failed to create activation context for %s: 0x%X.", LPCWSTR(ManifestFile), hr);
			}

			try
			{
				if (!ActivateActCtx(hActivationCtx, &uActivatedActCtx))
					hr = AtlHresultFromLastError();
				else
					hr = S_OK;
			}
			catch (...)
			{
				hr = E_FAIL;
			}

			if (FAILED(hr))
			{
				ReleaseActCtx(hActivationCtx);
				hActivationCtx = INVALID_HANDLE_VALUE;
				return SetSwitchEngineError(hr, L"Failed to activate %s: 0x%X.", LPCWSTR(ManifestFile), hr);
			}
		}
		else
		{
			hActivationCtx = INVALID_HANDLE_VALUE;
			uActivatedActCtx = 0;
		}

		// Activate ISwitchType.
		CComPtr<ISwitchType> pSwitchType;

		try
		{
			hr = pSwitchType.CoCreateInstance(SwitchId, NULL, CLSCTX_INPROC_SERVER);
		}
		catch (...)
		{
			hr = E_FAIL;
		}

		if (hActivationCtx != INVALID_HANDLE_VALUE)
		{
			if (DeactivateActCtx(0, uActivatedActCtx))
			{
				ReleaseActCtx(hActivationCtx);
				hActivationCtx = INVALID_HANDLE_VALUE;
			}
		}

		if (FAILED(hr))
			return SetSwitchEngineError(hr, L"Failed to activate ISwitchType for switch %s: 0x%X.", BSTR(strSwitchName), hr);

		return pSwitchType.CopyTo(result);
	}
	catch (...)
	{
		return SetSwitchEngineError(E_FAIL, L"Unhandled exception occurred.");
	}
}

HRESULT SwitcherEngine::SetError(HRESULT hr, LPCWSTR pszFormat, ...)
{
	va_list FormatArgs;
	va_start(FormatArgs, pszFormat);

	__try
	{
		return SetError(IID_NULL, hr, pszFormat, FormatArgs);
	}
	__finally
	{
		va_end(FormatArgs);
	}
}

HRESULT SwitcherEngine::SetError(REFIID InterfaceId, HRESULT hr, LPCWSTR pszFormat, va_list FormatArgs)
{
	CString strMessage;
	strMessage.FormatV(pszFormat, FormatArgs);
	return Error(strMessage, InterfaceId, hr);
}

HRESULT SwitcherEngine::SetSwitchEngineError(HRESULT hr, LPCWSTR pszFormat, ...)
{
	va_list FormatArgs;
	va_start(FormatArgs, pszFormat);

	__try
	{
		return SetError(__uuidof(ISwitchEngine), hr, pszFormat, FormatArgs);
	}
	__finally
	{
		va_end(FormatArgs);
	}
}
