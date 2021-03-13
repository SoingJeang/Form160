#include "peInject.h"
#include "GetProcgressAddress.h"

void main(int argc, TCHAR *argv[])
{
    TCHAR szProgram[MAX_PATH] = { "defiler.2.exe" }, szDll[MAX_PATH] = {"fortyFirstDll.dll"};
    if (argc < 3)
    {
        MessageBoxA(NULL, "You are using default exe and dll in debug", "warning", MB_OK);
    }
    else
    {
        _tcscpy(szProgram, argv[1]);
        _tcscpy(szDll, argv[2]);
    }
    
    // byte aa[4] = {};
    // DWORD dwA= 0x00401000;
    // memcpy(aa,(DWORD *)&dwA, 4);

    // if(!InjectToPe(szOldName, szNewName))
    //     MessageBoxA(NULL, "Error ", "Error", MB_OK);
    // else
    //     MessageBoxA(NULL, "Success", "Success", MB_OK);

    GetProcgressAddress(szDll);
}