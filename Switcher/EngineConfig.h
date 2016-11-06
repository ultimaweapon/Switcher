#pragma once

class CEngineConfig
{
public:
	CEngineConfig(REFGUID EngineId, LPCWSTR pszManifestFile, LPCWSTR lpManifestResName = NULL);
	~CEngineConfig();
public:
	REFGUID GetEngineId() const;
	const CString& GetManifestFile() const;
	LPCWSTR GetManifestResourceName() const;
private:
	GUID m_EngineId;
	CString m_strManifestFile;
	LPWSTR m_lpManifestResName;
private:
	CEngineConfig(const CEngineConfig&) {};
	CEngineConfig& operator=(const CEngineConfig&) {};
};
