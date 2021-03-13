#include "common.h"

FARPROC GetEntryAddressFromExe(LPCTSTR lpName);
BOOL GetWriteAddress(LPCTSTR lpName, DWORD dwMyFuncAddress, DWORD* pdwNewEntryAddress, DWORD* pdwWriteAddress, DWORD *pdwCallShift, DWORD *pdwOrderAddress);
BOOL InjectToPe(LPCTSTR lpName, LPCTSTR lpNewFileName);
