/*
 * @Author: Soingjeang
 * @Date: 2021-03-10 19:35:54
 * @LastEditors: SoingJeang
 * @LastEditTime: 2021-06-08 18:11:29
 * @FilePath: \cppFunc\PEInject\common.h
 */
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
unsigned circular_shift_left(unsigned value, int k);
unsigned circular_shift_right(unsigned value, int k);
int shift_arithmetic_left(int value, int k);
int shift_arithmetic_right(int value, int k);
unsigned logic_left(unsigned value, int k);
unsigned logic_right(unsigned value, int k);