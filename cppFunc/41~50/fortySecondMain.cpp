#include <windows.h>
#include <tchar.h>
#pragma comment(lib, "User32.lib")

typedef BOOL(*StartHooK)(HWND hWnd);

int WINAPI _tWinMain(HINSTANCE hInstExe, HINSTANCE, PTSTR oszCmdLine, int)
{
    HMODULE hDll = LoadLibrary(_T("fortySecondDll"));
    if (!hDll)
    {
        MessageBoxA(NULL, "LOader Erro fortySecondDll", "Err", MB_OK);
        return -1;
    }

    StartHooK pfnStarHook = NULL;
    pfnStarHook = (StartHooK)GetProcAddress(hDll, "StartHook");
    BOOL bRet = pfnStarHook(NULL);
    if (!bRet)
    {
        MessageBoxA(NULL, "Hook Erro fortySecondDll", "Err", MB_OK);
    }
    
    MessageBoxA(NULL, "Hook Success fortySecondDll", "Succ", MB_OK);
    
    return 0;
}
