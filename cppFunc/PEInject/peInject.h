/*
 * @Author: Soingjeang
 * @Date: 2021-03-10 14:02:56
 * @LastEditors: SoingJeang
 * @LastEditTime: 2021-03-16 16:08:26
 * @FilePath: \cppFunc\PEInject\peInject.h
 */
#include "common.h"

FARPROC GetEntryAddressFromExe(LPCTSTR lpName);
BOOL GetWriteAddress(LPCTSTR lpName, DWORD dwMyFuncAddress, DWORD* pdwNewEntryAddress, DWORD* pdwWriteAddress, DWORD *pdwCallShift, DWORD *pdwOrderAddress);
BOOL InjectToPe(LPCTSTR lpName, LPCTSTR lpNewFileName);
