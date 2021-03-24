/*
 * @Author: Soingjeang
 * @Date: 2021-03-24 20:08:50
 * @LastEditors: SoingJeang
 * @LastEditTime: 2021-03-24 20:19:42
 * @FilePath: \cppFunc\41~50\FiftythDll.cpp
 */
#include <windows.h>
#include <iostream>
#include "Tlhelp32.h"
#include <tchar.h>

#define DLL_EXPORT __declspec(dllexport)
#define ASM_DEF    __declspec(naked)

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

#define CODE_LENGTH 6
BYTE g_bOrder[CODE_LENGTH] = { 0x68, 0, 0, 0, 0, 0xc3 };
// 6A 00 68 cc 50 40
BYTE g_bOld_Order[CODE_LENGTH] = { 0, 0, 0, 0, 0, 0 };
// BYTE g_bOld_Order[CODE_LENGTH] = {0x6A, 0, 0x68, 0xcc, 0x50, 0x40};
DWORD g_InjectAddress = 0x4010C1;
DWORD g_ExeCallFunctionAddr = 0x4010D7;

int EnableDebugPriv(const TCHAR *name);
BOOL Init();
BOOL Exit();
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
void Inject();
void HookOn();
void HookOff();
void WriteMemory(LPVOID lpAddress, BYTE *pcode, int length);
void JudgeFunc(uintptr_t eax);

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

BOOL Exit()
{
	HookOff();
	return TRUE;
}

BOOL Init()
{
	MessageBoxA(NULL, "Injected! HookProc!", "Success!", MB_OK);
	EnableDebugPriv(SE_DEBUG_NAME);
	//DWORD dwPid = ::GetCurrentProcessId();
	g_hProcess = GetCurrentProcess();
	// g_hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, NULL, dwPid);
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

ASM_DEF void HookProc()
{
	__asm {
		pushfd
		pushad

		push	eax
		call	JudgeFunc

		popad
		popfd
        pop eax
		jmp		[g_ExeCallFunctionAddr]
    }
}

// 初始化时获得的 入口信息，拼接Shellcode
void Inject()
{
	if (g_bInjected)
		return;

	g_bInjected = TRUE;

	FARPROC pfnChangeTOMyAddre = (FARPROC)((DWORD)HookProc);
	memcpy(g_bOrder + 1, &pfnChangeTOMyAddre, 4);

	// get Old Code 
	// 属性打开
	DWORD dwOldProtect;
	if (!VirtualProtect((LPVOID)g_InjectAddress, CODE_LENGTH, PAGE_EXECUTE_READWRITE, &dwOldProtect))
	{
		char szInfo[1024];
		sprintf(szInfo, "Vp error-%d", GetLastError());
		MessageBoxA(NULL, szInfo, "init Info", MB_OK);
		return;
	}
	memcpy((void *)g_bOld_Order, (void *)g_InjectAddress, CODE_LENGTH);

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

// 钩子进来C级别入口
void JudgeFunc(uintptr_t eax)
{
    HookOff();

    // using code here

    HookOn();
}