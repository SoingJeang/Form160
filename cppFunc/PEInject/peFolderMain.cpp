/*
 * @Author: Soingjeang
 * @Date: 2021-03-11 18:50:25
 * @LastEditors: SoingJeang
 * @LastEditTime: 2021-03-16 14:34:04
 * @FilePath: \cppFunc\PEInject\peFolderMain.cpp
 */
#include "peInject.h"
#include "GetProcgressAddress.h"

void main(int argc, TCHAR *argv[])
{
    TCHAR szProgram[MAX_PATH] = { "defiler.2.exe" }, szDll[MAX_PATH] = { "MicroSpotData.dll" };
    CHAR szFuncName[] = "";
    if (argc < 3)
    {
        MessageBoxA(NULL, "You are using default exe and dll in debug", "warning", MB_OK);
    }
    else
    {
        _tcscpy(szProgram, argv[1]);
        _tcscpy(szDll, argv[2]);
    }

    PrintAllExportAddress(szDll);
    DWORD dwAddress = GetProcgressAddress(szDll, "CanUinitMicroSpot");
    HMODULE hDll = LoadLibrary(szDll);
    DWORD pAddressInDll = (DWORD)hDll + dwAddress;
    // FARPROC pFunc = (FARPROC)pAddressInDll;
    typedef int (*pCanUniDll)(int *);
    pCanUniDll pFunc = (pCanUniDll)pAddressInDll;
    int bBack, nRemain;
    bBack = pFunc(&nRemain);
}