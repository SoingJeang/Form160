/*
* @Author: Soingjeang
* @Date: 2021-03-19 17:40:55
 * @LastEditors: SoingJeang
 * @LastEditTime: 2021-03-23 19:11:32
 * @FilePath: \cppFunc\41~50\NotePadOrigin.cpp
*/

#include <Windows.h>
#include <tchar.h>
#include <commdlg.h>
#include <fstream>
#include <string>
#include "NotePadOrigin.h"
#include "resource.h"

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Gdi32.lib")
#pragma comment(lib, "Comdlg32.lib")

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("Typer");
	HWND         hwnd;
	MSG          msg;
	WNDCLASS     wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("Typing Program"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwndParent, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hwnd = NULL;
	char szEditName[] = "EDIT";

	switch (message)
	{
	case WM_CREATE:
	{
		hwnd = CreateWindowExA(NULL, szEditName, 0,
			WS_CHILD | WS_VISIBLE | WS_BORDER | WS_EX_NOPARENTNOTIFY,
			0, 0, 0, 0,
			hwndParent, (HMENU)1, *(HINSTANCE *)(lParam + 4), 0);

		// Create Menu
		HMENU hMenu = CreateMenu(), hPopMenu;
		hPopMenu = CreatePopupMenu();
		AppendMenu(hPopMenu, MF_STRING, CMD_FILE_OPEN, "Open");
		AppendMenu(hPopMenu, MF_STRING, CMD_FILE_SAVE, "Save");
		AppendMenu(hPopMenu, MF_STRING, CMD_FILE_EXIT, "Exit");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hPopMenu, "File");
		SetMenu(hwndParent, hMenu);
	}
		return 0;

	case WM_SIZE:
		MoveWindow(hwnd, 0, 0, LOWORD(lParam), HIWORD(lParam), 1);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_SETFOCUS:
		SetFocus(hwnd);
		return 0;

	case WM_COMMAND:
		// GetMenu(hwndParent);
		WORD wCase = LOWORD(wParam);
		switch (wCase)
		{
		case CMD_FILE_OPEN:
			FileOpenProc();
			break;

		case CMD_FILE_SAVE:
			FileSaveProc();
			break;

		case CMD_FILE_EXIT:
			ExitProc();
			break;
		}
		return DefWindowProc(hwndParent, message, wParam, lParam);
	}
	return DefWindowProc(hwndParent, message, wParam, lParam);
}

BOOL GetFilePath(PTCHAR pszPath)
{
	BOOL bRet = FALSE;
	if (nullptr == pszPath)
		return bRet;

	LPCTSTR szFilter = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = pszPath;
	ofn.lpstrFile[0] = _T('\0');
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = szFilter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (!GetOpenFileName(&ofn))
		bRet = FALSE;
	else
		bRet = TRUE;
		
	return bRet;
}

typedef struct _EnumWindowsArg
{
	HWND hTopWindow;
	DWORD dwProcessId;
}EnumWindowsArg, *PEnumWindowsArg;

typedef struct _EnumChindWinArg
{
	HWND hChildWindow;
	LPCTSTR lszClassName;
	BOOL bFound;
}EnumChindWinArg, *PEnumChindWinArg;

// 枚举顶级窗口回调
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	PEnumWindowsArg pEnumWin = (PEnumWindowsArg)lParam;
	DWORD dwPID = 0;
	GetWindowThreadProcessId(hwnd, &dwPID);
	if (dwPID == pEnumWin->dwProcessId)
	{
		pEnumWin->hTopWindow = hwnd;
		return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK EnumChildWindowsProc(HWND hwnd, LPARAM lParam)
{
	PEnumChindWinArg pEnumChild = (PEnumChindWinArg)lParam;
	TCHAR szClassName[MAX_PATH] = { 0 };
	GetClassName(hwnd, szClassName, MAX_PATH);
	_tcsupr_s(szClassName, MAX_PATH);
	if (_tcscmp(pEnumChild->lszClassName, szClassName)== 0)
	{
		pEnumChild->hChildWindow = hwnd;
		return FALSE;
	}

	// EnumChildWindows(hwnd, EnumChildWindowsProc, lParam);
	return TRUE;
}

// 用于获取顶级窗口
VOID GetWinDowHandle(LPCTSTR lszTitleName, LPCTSTR lszClassName, PHANDLE phandle)
{
	HWND hAll = ::GetDesktopWindow();
	HWND hCurrent = ::GetNextWindow(hAll, GW_CHILD);
	CHAR szTitleDbg[MAX_PATH] = { 0 };
	CHAR *p = NULL;

	while (NULL != hCurrent)
	{
		BOOL bNextCheck = FALSE;
		::GetWindowText(hCurrent, szTitleDbg, MAX_PATH);
		if (NULL != lszTitleName)
		{
			if (0 == _tcscmp(szTitleDbg, lszClassName))
			{
				bNextCheck = TRUE;
			}
		}
		if (bNextCheck)
		{
			::GetClassName(hCurrent, szTitleDbg, MAX_PATH);
			if (NULL != lszClassName)
			{
				if (0 == _tcscmp(szTitleDbg, lszClassName))
				{
					OutputDebugString(szTitleDbg);
					OutputDebugString(_T("\n"));
				}
			}
		}
		hCurrent = ::GetNextWindow(hCurrent, GW_HWNDNEXT);		
	}
}

HWND GetExpireWindow()
{
	EnumWindowsArg eWArg;
	EnumChindWinArg eCArg;

	eWArg.dwProcessId = GetCurrentProcessId();
	eWArg.hTopWindow = NULL;
	EnumWindows(EnumWindowsProc, (LPARAM)&eWArg);
	if (eWArg.hTopWindow != NULL)
	{
		eCArg.lszClassName = _T("EDIT");
		eCArg.hChildWindow = NULL;
		EnumChildWindows(eWArg.hTopWindow, EnumChildWindowsProc, (LPARAM)&eCArg);
	}
	return eCArg.hChildWindow;
}

int WINAPI FileOpenProc()
{
	int nRet = 0;
	int nFileLength = 0;
	TCHAR szFilePath[MAX_PATH] = {}, szBuffer[1024];
	std::ifstream mFileIn;
	HWND hwndEdit = GetExpireWindow();
	if (NULL == hwndEdit)
		return nRet;

	::SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM)(_T("")));
	GetFilePath(szFilePath);
	mFileIn.open(szFilePath, std::ios_base::in);
	if (!mFileIn.is_open() && !mFileIn)
		return false;
	mFileIn.seekg(0, std::ios::beg);
	while (!mFileIn.eof())
	{
		mFileIn.getline(szBuffer, 1024, _T('\n'));
		::SendMessage(hwndEdit, EM_SETSEL, LOWORD(-1), HIWORD(-1));
		::SendMessage(hwndEdit, EM_REPLACESEL, 0, (LPARAM)(szBuffer));
		::SendMessage(hwndEdit, EM_SETSEL, LOWORD(-1), HIWORD(-1));
		::SendMessage(hwndEdit, EM_REPLACESEL, 0, (LPARAM)(_T("\r\n")));
	}
	mFileIn.close();

	return nRet;
}

int WINAPI FileSaveProc()
{
	int nRet = 0;
	TCHAR szFilePath[MAX_PATH] = {};
	std::ofstream mFileOut;
	HWND hwndEdit = GetExpireWindow();
	if (NULL == hwndEdit)
		return nRet;

 	PTCHAR pBuffer;
	int len = GetWindowTextLength(hwndEdit);
	pBuffer = new CHAR[len + 2];
	GetWindowText(hwndEdit, pBuffer, len + 2);

	GetFilePath(szFilePath);
	mFileOut.open(szFilePath, std::ios_base::out | std::ios::trunc);
	if (!mFileOut.is_open() && !mFileOut)
		return false;

	mFileOut.write(reinterpret_cast<char *>(pBuffer), len);
	mFileOut.close();

	return nRet;
}

void WINAPI ExitProc()
{
	TerminateProcess(GetCurrentProcess(), 0);
}