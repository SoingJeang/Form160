
#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include <string>
#include  "Tlhelp32.h "
#pragma comment (lib,"Advapi32.lib")
#pragma comment (lib, "user32.lib")

using namespace std;
bool DllDeject(DWORD dwPid, LPCTSTR szDLlPath);
int EnableDebugPriv(const TCHAR * name);
DWORD GetProcPid(wchar_t *szExeName);
wstring AnsiToUnicode(string strAnsi);

void main(int argc, TCHAR *argv[])
{
    if (argc < 3)
    {
        MessageBoxA(NULL, "Parameater must 3!", "Error", MB_OK);
        return;
    }
        
    wchar_t szProcessName[MAX_PATH];
#ifdef UNICODE
    wcscpy(szProcessName, argv[1]);
#else
    wcscpy(szProcessName, AnsiToUnicode(argv[1]).c_str());
#endif
    
    DWORD dwPID = GetProcPid(szProcessName);
    
    if (DllDeject(dwPID, argv[2]))
    {
        if (argv[2])
            cout<<"Success "<< argv[2]<<endl;
    }
    else
    {
        cout<<"Failed "<< argv[2] << endl;
    }
    system("pause");
}

bool DllDeject(DWORD dwPid, LPCTSTR szDLlName)
{
    HANDLE hProcess = NULL, hThread = NULL;
    HMODULE hMod = NULL;
    LPVOID pRemoteDllName = NULL;
    DWORD dwDllBufferLen = (DWORD)((_tcslen(szDLlName) + 1) * sizeof(TCHAR));
    LPTHREAD_START_ROUTINE pTHreadProc = NULL;

    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
    if (NULL == hProcess)
    {
        return false;
    }

    pRemoteDllName = VirtualAllocEx(hProcess, NULL, dwDllBufferLen, MEM_COMMIT, PAGE_READWRITE);
    BOOL bOk = WriteProcessMemory(hProcess, pRemoteDllName, (LPVOID)szDLlName, dwDllBufferLen, NULL);
    if (!bOk)
        return false;

    hMod = GetModuleHandleA("kernel32.dll");
    pTHreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(hMod, "FreeLibraryA");
    hThread = CreateRemoteThread(hProcess, NULL, 0, pTHreadProc, pRemoteDllName, 0, NULL);

    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    CloseHandle(hProcess);
    return true;
}

int EnableDebugPriv(const TCHAR * name)
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tP;
    LUID luid;

    if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken))
    {
        cout << "OpenProcessToken error." << endl;
		return 1;
    }

    if(!LookupPrivilegeValue(NULL, name, &luid))
    {
        cout << "LookupPrivilege error!" << endl;
    }

    tP.PrivilegeCount = 1;
    tP.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    tP.Privileges[0].Luid = luid;
    if(!AdjustTokenPrivileges(hToken, 0, &tP, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
    {
        cout <<"AdjustTokenPrivileges error!"<<endl;
        CloseHandle(hToken);
		return 1;
    }
    CloseHandle(hToken);
	return 0;
}

DWORD GetProcPid(wchar_t *szExeName)
{
    EnableDebugPriv(SE_DEBUG_NAME);
    HANDLE hSnapshot1 = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if (hSnapshot1==INVALID_HANDLE_VALUE)
    {
		return 0;
	}
    PROCESSENTRY32W pInfo;
	pInfo.dwSize = sizeof(PROCESSENTRY32W);
    BOOL bRet = Process32FirstW(hSnapshot1,&pInfo);
    DWORD err = GetLastError();
    for (;bRet;bRet=Process32NextW(hSnapshot1,&pInfo))
	{
        wcsupr(szExeName);
        wcsupr(pInfo.szExeFile);
        if(0 == wcscmp(szExeName, pInfo.szExeFile))
        {
            DWORD dwPId = pInfo.th32ProcessID;
            CloseHandle(hSnapshot1);
            return dwPId;
        }
    }
    return 0;
}

wstring AnsiToUnicode(string strAnsi)
{
	if (strAnsi.empty())
	{
		return L"";
	}
	// ansi to unicode
	int nwcsLen = MultiByteToWideChar(CP_ACP, NULL, strAnsi.c_str(), strAnsi.length(), NULL, 0);
	wchar_t* pwszString = new wchar_t[nwcsLen + 1];

	MultiByteToWideChar(CP_ACP, NULL, strAnsi.c_str(), strAnsi.length(), pwszString, nwcsLen);
	pwszString[nwcsLen] = '\0';

	wstring wstrRet = pwszString;

	if (pwszString != NULL)
	{
		delete []pwszString;
		pwszString = NULL;
	}

	return wstrRet;
}