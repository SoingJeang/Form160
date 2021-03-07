#include <windows.h>
#include <string>
#pragma comment(lib, "User32.lib")

#define DLL_EXPORT __declspec(dllexport)

DWORD g_dwEAX, g_dwEBX;
DWORD *g_pfnAddress = (DWORD *)0x42F3C0;
    //      {
    //         mov ds:[xxxxxx],eax
    //         mov ds:[xxxxxx],ebx
    //         push entry
    //         ret
    //     }
byte g_pOrder[] = { 0x89, 0x05, 0, 0, 0, 0, 
                    0x89, 0x1D, 0, 0, 0, 0, 
                    0x68, 0, 0, 0, 0, 0xc3};
byte g_pOrEaxder[] = { 0x89, 0x05, 0, 0, 0, 0, 
                    0x68, 0, 0, 0, 0, 0xc3};

byte g_pOld_code[] = {0x53, 0x8B, 0xD8, 0x80, 0x7B, 0x2D, 
                        0x00, 0x74, 0x65, 0x66, 0x83, 0xBB, 
                        0x82, 0x00, 0x00, 0x00, 0x00, 0x74};

BOOL NameCheck()
{
    return TRUE;
}

// 执行自我命令函数
BOOL EntryFunc()
{
    // MessageBoxA(NULL, "Entey", "Fourth", MB_OK);
    PVOID lpEax = &g_dwEAX;
    char **ppszName = (char **)((byte *)g_dwEAX + 0x8);

    // 还原现场
    memcpy(g_pfnAddress, g_pOld_code, sizeof(g_pOrder));
    //MessageBoxA(NULL, "Get Info", "Third", MB_OK);
    
    __asm {
        mov eax, g_dwEAX
        // mov eax, g_dwEBX
        call g_pfnAddress
    }

    if (0 == strcmp("Exit1", *ppszName))
    {
        if(MessageBoxA(NULL, "Do you fickbirne really want to quit?", "Ask!", MB_YESNO))
            ExitProcess(0);
    }

    // MessageBoxA(NULL, "Hook Again", "Second", MB_OK);
    // 再次挂钩
    memcpy(g_pfnAddress, g_pOrEaxder, sizeof(g_pOrder));

    return TRUE;
}


BOOL hook_func(PROC pfnBoard, DWORD *pfnAddress)
{
    DWORD oldProtect;
    LPVOID lpEax = &g_dwEAX, lpEbx = &g_dwEBX;

    memcpy(g_pOrder + 2, &lpEax, 4);
    memcpy(g_pOrder + 8, &lpEbx, 4);
    memcpy(g_pOrder + 13, &pfnBoard, 4);

    // 写属性打开
    if (!VirtualProtect((LPVOID)pfnAddress, 32, PAGE_EXECUTE_READWRITE, &oldProtect))
        return FALSE;
    memcpy(pfnAddress, g_pOrder, 18);
    return TRUE;
}

// test without ebx
BOOL hook_func_eax(PROC pfnBoard, DWORD *pfnAddress)
{
    DWORD oldProtect;
    LPVOID lpEax = &g_dwEAX;

    memcpy(g_pOrEaxder + 2, &lpEax, 4);
    memcpy(g_pOrEaxder + 7, &pfnBoard, 4);

    // 写属性打开
    if (!VirtualProtect((LPVOID)pfnAddress, 32, PAGE_EXECUTE_READWRITE, &oldProtect))
        return FALSE;
    memcpy(pfnAddress, g_pOrEaxder, 18);
    return TRUE;
}

BOOL hook_Imediate_func(PROC pfnBoard, DWORD *pfnAddress)
{
    DWORD oldProtect;

    // push 0xaaaaaaaa ;目标函数地址
    // ret ;call 目标函数地址
    byte pOrder[6] = {};
    pOrder[0] = 0x68; // push
    pOrder[5] = 0xc3; // ret
    memcpy(pOrder + 1, &pfnBoard, 4);

    // 写属性打开
    if (!VirtualProtect((LPVOID)pfnAddress, 8, PAGE_EXECUTE_READWRITE, &oldProtect))
        return FALSE;
    memcpy(pfnAddress, pOrder, 6);
    return TRUE;
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{

    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // 入口点
        if (!hook_func_eax((PROC)EntryFunc, g_pfnAddress))
            MessageBoxA(NULL, "Dll inject error", "FortyFirst", MB_OK);
        break;

    case DLL_PROCESS_DETACH:
        // 脱钩
        memcpy(g_pfnAddress, g_pOld_code, sizeof(g_pOrder));
        break;
    }
    return TRUE; // succesful
}
