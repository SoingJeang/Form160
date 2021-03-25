/*
 * @Author: Soingjeang
 * @Date: 2021-03-23 18:47:07
 * @LastEditors: SoingJeang
 * @LastEditTime: 2021-03-25 15:13:25
 * @FilePath: \cppFunc\41~50\NotePadOrigin.h
 */

int WINAPI FileOpenProc();
int WINAPI FileSaveProc();
void WINAPI ExitProc();
BOOL GetFilePath(PTCHAR pszPath);
HWND GetExpireWindow(LPCTSTR szClassName, LPCTSTR szTitleName);