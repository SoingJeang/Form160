#pragma once 

#include <string>
#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <future>
#include <filesystem>

std::string UnicodeToAnsi(std::wstring wstrUnicode);
std::wstring AnsiToUnicode(std::string strAnsi);