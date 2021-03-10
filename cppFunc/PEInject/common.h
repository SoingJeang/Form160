#pragma once 

#include <string>
#include <tchar.h>
#include <windows.h>

std::string UnicodeToAnsi(std::wstring wstrUnicode);
std::wstring AnsiToUnicode(std::string strAnsi);