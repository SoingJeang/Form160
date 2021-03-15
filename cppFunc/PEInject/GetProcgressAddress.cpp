#include "PE.h"

using namespace std;

FARPROC GetProcgressAddress(LPCTSTR lpName)
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
        dwOrdinals = (DWORD)(dwOrdinals + i * 2);
        dwFunctions = (DWORD)(dwFunctions + i * 4);
        dwNames = (DWORD)(dwNames + i * 4);
        szFunctionName = (char *)(PE::RVAToOffset(parsedPe, *(PDWORD)(pPeFile + dwNames)) + pPeFile);
        printf("Ordinal : 0x%04X\n", *(PDWORD)(pPeFile + dwOrdinals));
        if (i == *(PWORD)(pPeFile + dwOrdinals))
        {
            printf("Names : %s\n", szFunctionName);
        }
        printf("Address : 0x%04X\n", *(PDWORD)(pPeFile + dwFunctions));
    }

    return NULL;
}