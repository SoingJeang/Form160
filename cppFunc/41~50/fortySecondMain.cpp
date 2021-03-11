#include <windows.h>
#include <tchar.h>
#pragma comment(lib, "User32.lib")

using namespace std;
HANDLE OpenInjectProcessSuspend(TCHAR *pszExeName, PHANDLE pHthread = NULL);
BOOL InjectInSuspend(HANDLE hProcess, TCHAR *pszDLlPath);

void main(int argc, TCHAR *argv[])
{
    TCHAR szProgram[MAX_PATH] = { "41~50\\defiler.2.exe" }, szDll[MAX_PATH] = {"fortySecondDll.dll"};
    HANDLE hProcess = NULL, hThread = NULL;
    if (argc < 3)
    {
        MessageBoxA(NULL, "You are using default exe and dll in debug", "warning", MB_OK);
    }
    else
    {
        _tcscpy(szProgram, argv[1]);
        _tcscpy(szDll, argv[2]);
    }
    
    hProcess = OpenInjectProcessSuspend(szProgram, &hThread);
    if(!hProcess)
    {
        MessageBoxA(NULL, "Open Process Fail", "Error", MB_OK);
        return;
    }
    if(!InjectInSuspend(hProcess, szDll))
    {
        MessageBoxA(NULL, "Inject FAil!", "Error", MB_OK);
        return;
    }
    ResumeThread(hThread);

    MessageBoxA(NULL, "Inject Success", "Success", MB_OK);

}

HANDLE OpenInjectProcessSuspend(TCHAR *pszExeName, PHANDLE pHthread)
{
    STARTUPINFO si;
	PROCESS_INFORMATION pi;
    HANDLE hProcess = NULL;

	ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.wShowWindow = SW_SHOW;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    ZeroMemory(&pi, sizeof(pi));
    if(!CreateProcess(pszExeName, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi))
        return NULL;
    hProcess = pi.hProcess;
    *pHthread = pi.hThread;
    return hProcess;
}

BOOL InjectInSuspend(HANDLE hProcess, TCHAR *pszDLlPath)
{
    if (NULL == hProcess)
        return FALSE;

    BOOL bRet = FALSE;
    HMODULE hMod = NULL;
    LPTHREAD_START_ROUTINE lpLoadLibrary = NULL;
    HANDLE hRemoteThread = NULL;

    DWORD dwDllBufferLen = (DWORD)((_tcslen(pszDLlPath) + 1) * sizeof(TCHAR));
    LPVOID pRemoteDllName = VirtualAllocEx(hProcess, NULL, dwDllBufferLen, MEM_COMMIT, PAGE_READWRITE);
    if(!WriteProcessMemory(hProcess, pRemoteDllName, (LPVOID)pszDLlPath, dwDllBufferLen, NULL))
        return bRet;

    hMod = GetModuleHandle(_T("kernel32.dll"));
    lpLoadLibrary = (PTHREAD_START_ROUTINE)GetProcAddress(hMod, "LoadLibraryA");
    if(!lpLoadLibrary)
        return bRet;

    hRemoteThread = CreateRemoteThread(hProcess, NULL, 0, lpLoadLibrary, pRemoteDllName, 0, NULL);
    if(!hRemoteThread)
        return bRet;
    WaitForSingleObject(hRemoteThread, INFINITE);
    CloseHandle(hRemoteThread);
    bRet = TRUE;
    return bRet;
}