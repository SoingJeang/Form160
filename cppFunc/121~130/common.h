/*
 * @Author: Soingjeang
 * @Date: 2021-03-10 19:35:54
 * @LastEditors: SoingJeang
 * @LastEditTime: 2021-06-09 15:13:02
 * @FilePath: \Form160\cppFunc\121~130\common.h
 */
#pragma once 

#include <string>
#include <tchar.h>
#include <stdio.h>
#include <fstream>
#include <future>
#include <filesystem>
#include "auto_tchar.h"

#ifdef _WIN32
#include <windows.h>
#endif

std::string UnicodeToAnsi(std::wstring wstrUnicode);
std::wstring AnsiToUnicode(std::string strAnsi);
unsigned circular_shift_left(unsigned value, int k);
unsigned circular_shift_right(unsigned value, int k);
int shift_arithmetic_left(int value, int k);
int shift_arithmetic_right(int value, int k);
unsigned logic_left(unsigned value, int k);
unsigned logic_right(unsigned value, int k);