/*
 * @Author: Soingjeang
 * @Date: 2021-03-10 19:39:24
 * @LastEditors: SoingJeang
 * @LastEditTime: 2021-06-08 18:51:03
 * @FilePath: \cppFunc\121~130\common.cpp
 */
#include "common.h"

std::wstring AnsiToUnicode(std::string strAnsi)
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

	std::wstring wstrRet = pwszString;

	if (pwszString != NULL)
	{
		delete []pwszString;
		pwszString = NULL;
	}

	return wstrRet;
}

std::string UnicodeToAnsi(std::wstring wstrUnicode)
{
	if (wstrUnicode.empty())
	{
		return "";
	}
	// unicode to ansi
	int nAnsiLen = WideCharToMultiByte(CP_ACP, NULL, wstrUnicode.c_str(), wstrUnicode.length(), NULL, 0, NULL, NULL);
	char* pszAnsi = new char[nAnsiLen + 1];

	WideCharToMultiByte(CP_ACP, NULL, wstrUnicode.c_str(), wstrUnicode.length(), pszAnsi, nAnsiLen, NULL, NULL);
	pszAnsi[nAnsiLen] = '\0';

	std::string strRet = pszAnsi;
	if (pszAnsi != NULL)
	{
		delete []pszAnsi; 
		pszAnsi = NULL;
	}

	return strRet;
}

unsigned circular_shift_left(unsigned value, int k)
{
	unsigned uRet = value << k;
	uRet |= value >> (32 - k);
	return uRet;
}

unsigned circular_shift_right(unsigned value, int k)
{
	unsigned uRet = value >> k;
	uRet |= value << (32 - k);
	return uRet;
}

int shift_arithmetic_left(int value, int k)
{
	int nRet = value << k;
	return nRet;
}

int shift_arithmetic_right(int value, int k)
{
	int nRet = value >> k;
	return nRet;
}

unsigned logic_left(unsigned value, int k)
{
	unsigned uRet = value << k;
	return uRet;
}

unsigned logic_right(unsigned value, int k)
{
	unsigned uRet = value >> k;
	return uRet;
}