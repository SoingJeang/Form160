/*
 * @Author: Soingjeang
 * @Date: 2021-03-11 18:57:53
 * @LastEditors: SoingJeang
 * @LastEditTime: 2021-03-16 11:31:54
 * @FilePath: \cppFunc\PEInject\GetProcgressAddress.h
 */
#include "common.h"

DWORD GetProcgressAddress(LPCTSTR lpName, PCHAR pszFuncName);
DWORD GetProcgressAddressInMempry(LPCTSTR lpName, PCHAR pszFuncName);
BOOL PrintAllExportAddress(LPCTSTR lpName);