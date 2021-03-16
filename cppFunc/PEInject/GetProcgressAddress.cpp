/*
 * @Author: Soingjeang
 * @Date: 2021-03-11 17:31:36
 * @LastEditors: SoingJeang
 * @LastEditTime: 2021-03-16 14:15:02
 * @FilePath: \cppFunc\PEInject\GetProcgressAddress.cpp
 */
#include "PE.h"
#include "common.h"

using namespace std;

/**
 * @description: 从pe层获得函数地址
 * @param {LPCTSTR} lpName 动态库名称
 * @param {PCHAR} pszFuncName 欲查找函数名称
 * @return {*}
 */
DWORD GetProcgressAddress(LPCTSTR lpName, PCHAR pszFuncName)
{
#ifdef UNICODE  
    string fileName = UnicodeToAnsi(lpName);
#else
    string fileName = lpName;
#endif
    tuple<bool, char *, fstream::pos_type> bin = PE::OpenBinary(fileName);
    char *pPeFile = get<1>(bin);
    auto parsedPe = PE::ParsePE(pPeFile);
    char *szFunctionName;
    DWORD dwCount, dwOrdinals, dwFunctions, dwNames;
    dwCount = parsedPe.ies.NumberOfFunctions;
    dwOrdinals = PE::RVAToOffset(parsedPe, parsedPe.ies.AddressOfNameOrdinals);
    dwFunctions = PE::RVAToOffset(parsedPe, parsedPe.ies.AddressOfFunctions);
    dwNames = PE::RVAToOffset(parsedPe, parsedPe.ies.AddressOfNames);
    for (DWORD i = 0; i < dwCount; i++)
    {
        
        szFunctionName = (char *)(PE::RVAToOffset(parsedPe, *(PDWORD)(pPeFile + dwNames)) + pPeFile);
        WORD wOrdinal = *(PWORD)(pPeFile + dwOrdinals);        
        
        if (0 == strcmp(szFunctionName, pszFuncName))
            return (DWORD)*(PDWORD)(pPeFile + dwFunctions + wOrdinal * 4);

        dwOrdinals = (DWORD)(dwOrdinals + 2);
        dwNames = (DWORD)(dwNames +  4);
    }

    return 0;
}

DWORD GetProcgressAddressInMempry(LPCTSTR lpName, PCHAR pszFuncName)
{
    return 0;
}

BOOL PrintAllExportAddress(LPCTSTR lpName)
{
    BOOL bRet = FALSE;
#ifdef UNICODE
    string fileName = UnicodeToAnsi(lpName);
#else
    string fileName = lpName;
#endif
    tuple<bool, char *, fstream::pos_type> bin = PE::OpenBinary(fileName);
    char *pPeFile = get<1>(bin);
    auto parsedPe = PE::ParsePE(pPeFile);
    char *szFunctionName;
    DWORD dwCount, dwOrdinals, dwFunctions, dwNames;
    dwCount = parsedPe.ies.NumberOfFunctions;
    dwOrdinals = PE::RVAToOffset(parsedPe, parsedPe.ies.AddressOfNameOrdinals);
    dwFunctions = PE::RVAToOffset(parsedPe, parsedPe.ies.AddressOfFunctions);
    dwNames = PE::RVAToOffset(parsedPe, parsedPe.ies.AddressOfNames);
    for (DWORD i = 0; i < dwCount; i++)
    {
        WORD wOrdinal = *(PWORD)(pPeFile + dwOrdinals);
        szFunctionName = (char *)(PE::RVAToOffset(parsedPe, *(PDWORD)(pPeFile + dwNames)) + pPeFile);
        printf("Ordinal : 0x%04X\n", wOrdinal);
        printf("Names : %s\n", szFunctionName);
        printf("Address : 0x%04X\n\n", *(PDWORD)(pPeFile + dwFunctions + wOrdinal * 4));
        dwOrdinals = (DWORD)(dwOrdinals + 2);
        dwNames = (DWORD)(dwNames +  4);
    }

    bRet = TRUE;
    return bRet;
}