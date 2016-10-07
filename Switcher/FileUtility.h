#pragma once

typedef BOOL (*FILE_ENUMERATE_HANDLER) (LPCWSTR pszDir, const WIN32_FIND_DATA *pFileDetails, LPVOID pContext);

UINT EnumerateFiles(LPCWSTR pszDir, FILE_ENUMERATE_HANDLER pfnHandler, LPVOID pContext);
