#include <windows.h>
#include <iostream>
#include "Tlhelp32.h"
#include <tchar.h>

#define DLL_EXPORT __declspec(dllexport)

using namespace std;
#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "User32.lib")

#pragma data_seg("Share")
HINSTANCE g_hInstance = NULL; // this instance of dll;
HHOOK g_hHook = NULL;         // this global hook
HWND g_hWnd = NULL;           // exe's Windows handle;
#pragma data_seg()
#pragma comment(linker, "/Section:Share,rws")
HANDLE g_hProcess = NULL;
BOOL g_bInjected = FALSE;

// {
//     cmp eax,0 
//     jz 06
//     push xxxxxx
//     ret 
//     cmp eax, 2
//     jz 02
//     push xxxx
//     ret
//     cmp eax, 4
//     jz 02
//     ret 
// }
// BYTE g_bOrder[CODE_LENGTH] = {  0x89, 0x05, 0, 0, 0, 0, 
//                                 0x89, 0x1D, 0, 0, 0, 0, 
//                                 0x68, 0, 0, 0, 0, 0xc3};

// {
//     push xxxxxxxx
//     retn
// }

#define CODE_LENGTH 6
BYTE g_bOrder[CODE_LENGTH] = {0x68, 0, 0, 0, 0, 0xc3};
// 6A 00 68 cc 50 40
BYTE g_bOld_Order[CODE_LENGTH] = {0, 0, 0, 0, 0, 0};
// BYTE g_bOld_Order[CODE_LENGTH] = {0x6A, 0, 0x68, 0xcc, 0x50, 0x40};
DWORD g_InjectAddress = 0x4011FA;
DWORD g_ExeCallFunctionAddr = 0x40120d;

int EnableDebugPriv(const TCHAR *name);
BOOL Init();
BOOL Exit();
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
void Inject();
void HookOn();
void HookOff();
void WriteMemory(LPVOID lpAddress, BYTE *pcode, int length);
void JudgeFunc();
int WINAPI FileOpenProc();
int WINAPI FileSaveProc();
void WINAPI ExitProc();

typedef int(WINAPI *OpenFileF)();
typedef int(WINAPI *SaveFileF)();
typedef void(WINAPI *ExitF)();

OpenFileF g_pfnOpenFileNew = NULL;
SaveFileF g_pfnSaveFileNew = NULL;
ExitF g_pfnExitProcNew = NULL;
DWORD g_pfnOPenOld = 0;
DWORD g_pfnSaveOld = 0;
DWORD g_pfnExitOld = 0;
DWORD g_addrOPen = 0x401260; // 按钮进入地址
DWORD g_addrSave = 0x401270;
DWORD g_addrExit = 0x401268;

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        g_hInstance = hinstDLL;
        Init();
        break;

    case DLL_PROCESS_DETACH:
        // 脱钩
        Exit();
        break;
    }
    return TRUE; // succesful
}

int EnableDebugPriv(const TCHAR *name)
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tP;
    LUID luid;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
    {
        cout << "OpenProcessToken error." << endl;
        return 1;
    }

    if (!LookupPrivilegeValue(NULL, name, &luid))
    {
        cout << "LookupPrivilege error!" << endl;
    }

    tP.PrivilegeCount = 1;
    tP.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    tP.Privileges[0].Luid = luid;
    if (!AdjustTokenPrivileges(hToken, 0, &tP, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
    {
        cout << "AdjustTokenPrivileges error!" << endl;
        CloseHandle(hToken);
        return 1;
    }
    CloseHandle(hToken);
    return 0;
}

// 进程全hook
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (g_hHook)
        return CallNextHookEx(g_hHook, nCode, wParam, lParam);
    return 0;
}

BOOL StartHook(HWND hWnd)
{
    BOOL bRet = FALSE;
    g_hWnd = hWnd;
    g_hHook = ::SetWindowsHookEx(WH_MOUSE, MouseProc, g_hInstance, 0);
    if (g_hHook)
        bRet = TRUE;
    return bRet;
}

BOOL StopHook()
{
    BOOL bRet = FALSE;
    HookOff();
    if (g_hHook != NULL)
    {
        UnhookWindowsHookEx(g_hHook);
        FreeLibrary(g_hInstance);
    }
    return bRet;
}

BOOL Init()
{
    EnableDebugPriv(SE_DEBUG_NAME);
    DWORD dwPid = ::GetCurrentProcessId();
    g_hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, NULL, dwPid);
    if (NULL == g_hProcess)
    {
        char szFail[1024] = {};
        sprintf(szFail, "OpenProcess fail， and error code = %d", GetLastError());
        MessageBoxA(NULL, szFail, "Error", MB_OK);
        return FALSE;
    }

    Inject();
    return TRUE;
}

BOOL Exit()
{
    HookOff();
    return TRUE;
}

// 初始化时获得的 入口信息，拼接Shellcode
void Inject()
{
    if (g_bInjected)
        return;

    g_bInjected = TRUE;

    FARPROC pfnChangeTOMyAddre = (FARPROC)((DWORD)JudgeFunc);
    memcpy(g_bOrder + 1, &pfnChangeTOMyAddre, 4);

    // get Old Code 
    // 属性打开
    DWORD dwOldProtect;
    if (!VirtualProtect((LPVOID)g_InjectAddress, CODE_LENGTH, PAGE_EXECUTE_READWRITE, &dwOldProtect))
    {
        char szInfo[1024];
        sprintf(szInfo,"Vp error-%d", GetLastError());
        MessageBoxA(NULL, szInfo, "init Info", MB_OK);
        return;
    }
    memcpy((void *)g_bOld_Order, (void *)g_InjectAddress, CODE_LENGTH);

    char szInfo[1024];
    sprintf(szInfo, "Old Code : %p", (DWORD *)g_bOld_Order[0]);
    MessageBoxA(NULL, szInfo, "init Info", MB_OK);
    
    HookOn();
}

void HookOn()
{
    if (NULL == g_hProcess)
        return;

    WriteMemory((void *)g_InjectAddress, (PBYTE)g_bOrder, CODE_LENGTH);
}

void HookOff()
{
    WriteMemory((void *)g_InjectAddress, (PBYTE)g_bOld_Order, CODE_LENGTH);
}

void WriteMemory(LPVOID lpAddress, BYTE *pcode, int length)
{
    DWORD dwOldProtect, dwRet, dwWrited;
    if (NULL == g_hProcess)
        return;
    if (!VirtualProtect(lpAddress, length, PAGE_EXECUTE_READWRITE, &dwOldProtect))
        return;
    dwRet = WriteProcessMemory(g_hProcess, lpAddress, pcode, length, &dwWrited);
    if (0 == dwRet || 0 == dwWrited)
    {
        MessageBoxA(NULL, " 写入内存失败", "Err", MB_OK);
    }
    VirtualProtectEx(g_hProcess, lpAddress, length, dwOldProtect, NULL);
}

void JudgeFunc()
{
    HookOff();
    
    ::MessageBoxA(NULL, "JudgeFunc", "lpCation", MB_OK);

    __asm
    {
        call g_InjectAddress
    }
}

int WINAPI FileOpenProc()
{
    ::MessageBoxA(NULL, "OpenProc ", "lpCation", MB_OK);
    int nRet = 0;
    HookOff();

    // nRet = ::MessageBoxA(hWnd, "MessageBoxA be HOOKen ", lpCation, uType);
    // // nRet = ::MessageBoxA(NULL, lpText, lpCation, uType);

    HookOn();
    return nRet;
}

int WINAPI FileSaveProc()
{
    int nRet = 0;
    HookOff();

    ::MessageBoxA(NULL, "File Save ", "lpCation", MB_OK);
    // nRet = ::MessageBoxA(hWnd, "MessageBoxA be HOOKen ", lpCation, uType);
    // // nRet = ::MessageBoxA(NULL, lpText, lpCation, uType);

    HookOn();
    return nRet;
}

void WINAPI ExitProc()
{
    int nRet = 0;
    HookOff();

    ::MessageBoxA(NULL, "File Exit ", "lpCation", MB_OK);
    // nRet = ::MessageBoxW(NULL, L"WMessageBoxW be HOOKed", lpCation, uType);
    // // nRet = ::MessageBoxW(NULL, lpText, lpCation, uType);

    HookOn();
    
    __asm
    {
        mov esp, ebp
        pop ebp
        jmp [g_addrExit]
    }
    ::MessageBoxA(NULL, "sss Exit ", "lpCation", MB_OK);
}