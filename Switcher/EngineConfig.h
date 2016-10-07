#pragma once

class CEngineConfig
{
public:
	CEngineConfig(REFGUID EngineId, LPCWSTR pszManifestFile);
public:
	REFGUID GetEngineId() const;
	const CString& GetManifestFile() const;
private:
	GUID m_EngineId;
	CString m_strManifestFile;
};
