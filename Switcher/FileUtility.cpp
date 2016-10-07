#include "PCH.h"
#include "FileUtility.h"

UINT EnumerateFiles(LPCWSTR pszDir, FILE_ENUMERATE_HANDLER pfnHandler, LPVOID pContext)
{
	ATLASSERT(pszDir);
	ATLASSERT(pfnHandler);

	CPath TargetDir(pszDir);
	if (!TargetDir.Append(L"*"))
		AtlThrow(E_FAIL);

	WIN32_FIND_DATA FileDetails = { 0 };
	HANDLE hFindFile = FindFirstFile(TargetDir, &FileDetails);
	if (hFindFile == INVALID_HANDLE_VALUE)
		AtlThrowLastWin32();

	UINT uSucceeded = 0;

	try
	{
		do
		{
			if (wcscmp(FileDetails.cFileName, L".") == 0 || wcscmp(FileDetails.cFileName, L"..") == 0)
				continue; // Skip parent and current directory.

			if (!pfnHandler(pszDir, &FileDetails, pContext))
				goto CleanUp;

			uSucceeded++;
		} while (FindNextFile(hFindFile, &FileDetails));

		DWORD dwError = GetLastError();
		if (dwError != ERROR_NO_MORE_FILES)
			AtlThrow(HRESULT_FROM_WIN32(dwError));
	}
	catch (...)
	{
		ATLTRY(FindClose(hFindFile));
		throw;
	}

	CleanUp:
	FindClose(hFindFile);

	return uSucceeded;
}
