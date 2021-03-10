#include "windowHook.h"
#include "Tlhelp32.h"

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

typedef int(WINAPI *TypeMsgBoxA)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
typedef int(WINAPI *TypeMsgBoxW)(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType);
TypeMsgBoxA g_pfnOldMessageBoxA = NULL;
TypeMsgBoxW g_pfnOldMessageBoxW = NULL;
FARPROC g_pfnMsgBoxA = NULL; // 地址位置
FARPROC g_pfnMsgBoxW = NULL;

#define CODE_LENGTH 5
BYTE g_bOldMsgBoxACode[CODE_LENGTH];
BYTE g_bOldMsgBoxWCode[CODE_LENGTH];
BYTE g_bNewMsgBoxACode[CODE_LENGTH];
BYTE g_bNewMsgBoxWCode[CODE_LENGTH];

int EnableDebugPriv(const TCHAR *name);
BOOL Init();
BOOL Exit();
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
void Inject();
void HookOn();
void HookOff();
void WriteMemory(LPVOID lpAddress, BYTE *pcode, int length);
int WINAPI MyMessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCation, UINT uType);
int WINAPI MyMessageBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCation, UINT uType);

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

    MessageBoxA(NULL, "init", "Info", MB_OK);
    Inject();
    return TRUE;
}

BOOL Exit()
{
    HookOff();
    return TRUE;
}

void Inject()
{
    if (g_bInjected)
        return;

    g_bInjected = TRUE;

    HMODULE hModule = ::LoadLibrary(_T("User32.dll"));
    if (!hModule)
    {
        MessageBoxA(NULL, "获取 User32.dll 失败", "Error", MB_OK);
        return;
    }
    g_pfnOldMessageBoxA = (TypeMsgBoxA)::GetProcAddress(hModule, "MessageBoxA");
    g_pfnOldMessageBoxW = (TypeMsgBoxW)::GetProcAddress(hModule, "MessageBoxW");

    g_pfnMsgBoxA = (FARPROC)g_pfnOldMessageBoxA;
    g_pfnMsgBoxW = (FARPROC)g_pfnOldMessageBoxW;
    if (NULL == g_pfnMsgBoxA || NULL == g_pfnMsgBoxW)
    {
        MessageBoxA(NULL, "获取 MessageBoxA 函数失败", "Error", MB_OK);
        return;
    }

    char szInfo[1024];
    sprintf(szInfo, "OldMsgA addr is :0x%p, \nOldMsgW addr is :0x%p", g_pfnMsgBoxA, g_pfnMsgBoxW);
    // MessageBoxA(NULL, szInfo, "Info", MB_OK);
    sprintf(szInfo, "MyMsgA addr is :0x%p, \nMyMsgW addr is :0x%p", MyMessageBoxA, MyMessageBoxW);
    // MessageBoxA(NULL, szInfo, "Info", MB_OK);

    __asm
        {
        lea edi, g_bOldMsgBoxACode
        mov esi, g_pfnMsgBoxA
        cld
        mov ecx, CODE_LENGTH
        rep movsb
        lea edi, g_bOldMsgBoxWCode
        mov esi, g_pfnMsgBoxW
        cld
        mov ecx, CODE_LENGTH
        rep movsb
        }

    // 将新地址复制到入口
    g_bNewMsgBoxACode[0] = g_bNewMsgBoxWCode[0] = 0xe9; // jmp 间接寻址
    __asm {
        lea eax, MyMessageBoxA
        mov ebx, g_pfnMsgBoxA
        sub eax, ebx
        sub eax, CODE_LENGTH
        mov dword ptr ds:[g_bNewMsgBoxACode + 1], eax
        lea eax, MyMessageBoxW
        mov ebx, g_pfnMsgBoxW
        sub eax, ebx
        sub eax, CODE_LENGTH
        mov dword ptr [g_bNewMsgBoxWCode + 1], eax
    }

    string strOutA = "New InfoA is :", strOutW = "New InfoW is :";
    for(int i=0;i<CODE_LENGTH; ++i)
    {
        sprintf(szInfo, "%0X", g_bNewMsgBoxACode[i]);
        strOutA += szInfo;
        sprintf(szInfo, "%0X", g_bNewMsgBoxWCode[i]);
        strOutW += szInfo;
    }
    // MessageBoxA(NULL, (strOutA+strOutW).c_str(), "Info", MB_OK);

    HookOn();
}

void HookOn()
{
    if (NULL == g_hProcess)
        return;
    //::MessageBoxA(NULL, "Ready for Hook ", "lpCation", MB_OK);
    WriteMemory(g_pfnMsgBoxA, g_bNewMsgBoxACode, CODE_LENGTH);
    WriteMemory(g_pfnMsgBoxW, g_bNewMsgBoxWCode, CODE_LENGTH);
    //::MessageBoxA(NULL, "HOOKed ", "lpCation", MB_OK);
}

void HookOff()
{
    WriteMemory(g_pfnMsgBoxA, g_bOldMsgBoxACode, CODE_LENGTH);
    WriteMemory(g_pfnMsgBoxW, g_bOldMsgBoxWCode, CODE_LENGTH);
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

int WINAPI MyMessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCation, UINT uType)
{

    int nRet = 0;
    HookOff();

    nRet = ::MessageBoxA(hWnd, "MessageBoxA be HOOKen ", lpCation, uType);
    // nRet = ::MessageBoxA(NULL, lpText, lpCation, uType);

    HookOn();
    return nRet;
}

int WINAPI MyMessageBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCation, UINT uType)
{

    int nRet = 0;
    HookOff();

    nRet = ::MessageBoxW(NULL, L"WMessageBoxW be HOOKed", lpCation, uType);
    // nRet = ::MessageBoxW(NULL, lpText, lpCation, uType);

    HookOn();
    return nRet;
}