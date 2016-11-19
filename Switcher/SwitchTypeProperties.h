#pragma once

#include "SwitchTypeConfig.h"

#include "Engine_h.h"

class ATL_NO_VTABLE SwitchTypeProperties :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<SwitchTypeProperties>,
	public ISwitchTypeProperties
{
public:
	SwitchTypeProperties(const SwitchTypeProperties&) = delete;

	DECLARE_NO_REGISTRY()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(SwitchTypeProperties)
		COM_INTERFACE_ENTRY(ISwitchTypeProperties)
	END_COM_MAP()

	SwitchTypeProperties& operator=(const SwitchTypeProperties&) = delete;

	const SwitchTypeConfig * GetConfig() const;
	LPCWSTR GetDirectory() const;
	LPCWSTR GetName() const;
	VOID SetConfig(SwitchTypeConfig *pConfig);
	VOID SetDirectory(LPCWSTR pszDirectory);
	VOID SetName(LPCWSTR pszName);

	virtual HRESULT STDMETHODCALLTYPE get_Config(ISwitchTypeConfig **result);
	virtual HRESULT STDMETHODCALLTYPE get_Directory(BSTR *result);
	virtual HRESULT STDMETHODCALLTYPE get_Name(BSTR *result);
protected:
	SwitchTypeProperties();
	~SwitchTypeProperties();
private:
	CComPtr<SwitchTypeConfig> conf;
	std::tr2::sys::path dir;
	std::wstring name;
};
