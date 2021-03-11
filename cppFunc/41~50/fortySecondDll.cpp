#include <windows.h>
#include <string>
#pragma comment(lib, "User32.lib")

#define DLL_EXPORT __declspec(dllexport)

DWORD g_dwEAX;
DWORD g_dwAddress = 0x401000;
    //      {
    //         mov ds:[xxxxxx],eax
    //         mov ds:[xxxxxx],ebx
    //         push entry
    //         ret
    //     }
#define CODE_LENGTH 0x13
byte g_pOrder[CODE_LENGTH] = { 0xE8, 0, 0, 0, 0, 0x90};

byte g_pOld_code[CODE_LENGTH] = { 0x6A, 0x40, 0x68, 0x00, 0x30, 0x40 };

// 执行自我命令函数
BOOL EntryFunc()
{
    // PVOID lpEax = &g_dwEAX;
    // char **ppszName = (char **)((byte *)g_dwEAX + 0x8);

    // // 还原现场
    // memcpy(g_pfnAddress, g_pOld_code, sizeof(g_pOrder));
    // //MessageBoxA(NULL, "Get Info", "Third", MB_OK);
    DWORD dwNewEntry = g_dwAddress + CODE_LENGTH;
    
    __asm {
        add esp,4
        jmp dwNewEntry
    }    

    // if (0 == strcmp("Exit1", *ppszName))
    // {
    //     if(MessageBoxA(NULL, "Do you fickbirne really want to quit?", "Ask!", MB_YESNO))
    //         ExitProcess(0);
    // }

    // // MessageBoxA(NULL, "Hook Again", "Second", MB_OK);
    // // 再次挂钩
    // memcpy(g_pfnAddress, g_pOrEaxder, sizeof(g_pOrder));

    return TRUE;
}


BOOL hook_func(DWORD dwPfnBoard, DWORD dwPfnAddress)
{
    DWORD oldProtect;
    LPVOID lpEax = &g_dwEAX;

    char szInfo[1024];
    // curraddr + xxx + 5 = dstadd
    DWORD dwCllDstAddr = dwPfnBoard - dwPfnAddress - 5 - 1;
    sprintf(szInfo ,"To fn address %p\n curr adress: %p\n diss:%d", (DWORD*)dwPfnBoard, (DWORD*)dwPfnAddress, dwCllDstAddr);
    memcpy(g_pOrder + 1, &dwCllDstAddr, 4);

    // 写属性打开
    if (!VirtualProtect((LPVOID)dwPfnAddress, 32, PAGE_EXECUTE_READWRITE, &oldProtect))
        return FALSE;
    memcpy((LPVOID)dwPfnAddress, g_pOrder, CODE_LENGTH);
    return TRUE;
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{

    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // 入口点
        if (!hook_func((DWORD)EntryFunc, g_dwAddress))
            MessageBoxA(NULL, "Dll inject error", "FortySecond", MB_OK);
        break;

    case DLL_PROCESS_DETACH:
        // 脱钩
        memcpy((LPVOID)g_dwAddress, g_pOld_code, sizeof(g_pOrder));
        break;
    }
    return TRUE; // succesful
}
