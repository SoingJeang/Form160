/*
* @Author: Soingjeang
* @Date: 2021-03-31 10:32:13
 * @LastEditors: SoingJeang
 * @LastEditTime: 2021-04-01 16:24:37
 * @FilePath: \cppFunc\51~60\fiftySecondMain.cpp
*/
#include <windows.h>
#include <iostream>
#include <memory.h>

using namespace std;

/*64 bit循环左移*/
unsigned __int64 rol64(unsigned __int64 val, int size)
{
	unsigned __int64 res = val << size;
	res |= val >> (64 - size);
	return res;
}

/*64 bit循环右移*/
unsigned __int64 ror64(unsigned __int64 val, int size)
{
	unsigned __int64 res = val >> size;
	res |= val << (64 - size);
	return res;
}


/*循环左移*/
unsigned rol(unsigned val, int size)
{
	unsigned res = val << size;
	res |= val >> (32 - size);
	return res;
}

/*循环右移*/
unsigned ror(unsigned val, int size)
{
	unsigned res = val >> size;
	res |= val << (32 - size);
	return res;
}

int firstEnCode(int* nameCode, int existCode)
{
	int v2, v3, v4, v5, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v18, v19, v20, v21, v36, result;
	int *v26;
	v2 = *(DWORD *)existCode;
	v3 = *(DWORD *)(existCode + 8);
	v4 = *(DWORD *)(existCode + 12);
	v5 = *(DWORD *)(existCode + 4);

	// 41b0b4
	byte vCheckPreLoop1[] = {
		0x78, 0xA4, 0x6A, 0xD7,   0x56, 0xB7, 0xC7, 0xE8,   0xDB, 0x70, 0x20, 0x24,   0xEE, 0xCE, 0xBD, 0xC1,
		0xAF, 0x0F, 0x7C, 0xF5,   0x2A, 0xC6, 0x87, 0x47,   0x13, 0x46, 0x30, 0xA8,   0x01, 0x95, 0x46, 0xFD,
		0xD8, 0x98, 0x80, 0x69,   0xAF, 0xF7, 0x44, 0x8B,   0xB1, 0x5B, 0xFF, 0xFF,   0xBE, 0xD7, 0x5C, 0x89,
		0x22, 0x11, 0x90, 0x6B,   0x93, 0x71, 0x98, 0xFD,   0x8E, 0x43, 0x79, 0xA6,   0x21, 0x08, 0xB4, 0x49
	};
	// 41b0f4
	byte vCheckPreLoop2[] = {
		0x62, 0x25, 0x1E, 0xF6,   0x40, 0xB3, 0x40, 0xC0,   0x51, 0x5A, 0x5E, 0x26,   0xAA, 0xC7, 0xB6, 0xE9,
		0x5D, 0x10, 0x2F, 0xD6,   0x53, 0x14, 0x44, 0x02,   0x81, 0xE6, 0xA1, 0xD8,   0xC8, 0xFB, 0xD3, 0xE7,
		0xE6, 0xCD, 0xE1, 0x21,   0xD6, 0x07, 0x37, 0xC3,   0x87, 0x0D, 0xD5, 0xF4,   0xED, 0x14, 0x5A, 0x45,
		0x05, 0xE9, 0xE3, 0xA9,   0xF8, 0xA3, 0xEF, 0xFC,   0xD9, 0x02, 0x6F, 0x67,   0x8A, 0x4C, 0x2A, 0x8D
	};

	// 41b034
	byte vCheckPreLoop3[] = {
		0x42, 0x39, 0xFA, 0xFF,   0x81, 0xF6, 0x71, 0x87,   0x22, 0x61, 0x9D, 0x6D,   0x0C, 0x38, 0xE5, 0xFD,
		0x44, 0xEA, 0xBE, 0xA4,   0xA9, 0xCF, 0xDE, 0x4B,   0x60, 0x4B, 0xBB, 0xF6,   0x70, 0xBC, 0xBF, 0xBE,
		0xC6, 0x7E, 0x9B, 0x28,   0xFA, 0x27, 0xA1, 0xEA,   0x85, 0x30, 0xEF, 0xD4,   0x05, 0x1D, 0x88, 0x04,
		0x39, 0xD0, 0xD4, 0xD9,   0xE5, 0x99, 0xDB, 0xE6,   0xF8, 0x7C, 0xA2, 0x1F,   0x65, 0x56, 0xAC, 0xC4
	};
	// 41b074
	byte vCheckPreLoop4[] = {
		0x44, 0x22, 0x29, 0xF4,   0x97, 0xFF, 0x2A, 0x43,   0xA7, 0x23, 0x94, 0xAB,   0x39, 0xA0, 0x93, 0xFC,
		0xC3, 0x59, 0x5B, 0x65,   0x92, 0xCC, 0x0C, 0x8F,   0x7D, 0xF4, 0xEF, 0xFF,   0xD1, 0x5D, 0x84, 0x85,
		0x4F, 0x7E, 0xA8, 0x6F,   0xE0, 0xE6, 0x2C, 0xFE,   0x14, 0x43, 0x01, 0xA3,   0xA1, 0x11, 0x08, 0x4E,
		0x82, 0x7E, 0x53, 0xF7,   0x35, 0xF2, 0x3A, 0xBD,   0xBB, 0xD2, 0xD7, 0x2A,   0x91, 0xD3, 0x86, 0xEB
	};


	int *pTempCheck = (int*)vCheckPreLoop1;
	char *pTempName = (char *)nameCode;
	for (int i = 0; i < 4; i++)
	{
		v2 = v5 + rol(*(int *)(pTempCheck)+(v5 & v3 | v4 &~v5) + v2 + *(DWORD *)pTempName, 7);
		v4 = v2 + rol(*(int *)(pTempCheck + 1) + (v2 & v5 | v3 & ~v2) + v4 + *(DWORD *)(pTempName + 4), 12);
		v3 = v4 + rol(*(int *)(pTempCheck + 2) + (v2 & v4 | v5 & ~v4) + v3 + *(DWORD *)(pTempName + 8), 17);
		v5 = v3 + rol(*(int *)(pTempCheck + 3) + (v3 & v4 | v2 & ~v3) + v5 + *(DWORD *)(pTempName + 12), 22);
		pTempCheck += 4;
		pTempName += 0x10;
	}

	pTempCheck = (int*)vCheckPreLoop2;
	pTempName = (char *)nameCode;
	for (int i = 1; i < 17; i += 4) // 4 times
	{
		v7 = rol(*(int *)(pTempCheck)+(v5 & v4 | v3 &~v4) + v2 + *(DWORD *)(pTempName + 4 * (i & 0xf)), 5);
		v2 = v5 + v7;
		v8 = rol(*(int *)(pTempCheck + 1) + ((v5 + v7) & v3 | v5 & ~v3) + v4 + *(DWORD *)(pTempName + 4 * ((i + 5) & 0xf)), 9);
		v4 = v2 + v8;
		v9 = rol(*(int *)(pTempCheck + 2) + (v5 & (v2 + v8) | v2 & ~v5) + v3 + *(DWORD *)(pTempName + 4 * ((i + 10) & 0xf)), 14);
		v3 = v4 + v9;
		v5 = v4 + v9 + rol(*(int *)(pTempCheck + 3) + (v2 & (v4 + v9) | v4 & ~v2) + v5 + *(DWORD *)(pTempName + 4 * ((i - 1) & 0xf)), 20);
		pTempCheck += 4;
	}

	v10 = v3 ^ v4;
	pTempCheck = (int*)vCheckPreLoop3;
	int nloopOdd = -5;
	for (int i = 0; i < 4; i++) // 4 times
	{
		v11 = rol(*(int *)(pTempCheck)+(v5 ^ v10) + v2 + *(DWORD *)(pTempName + 4 * (((BYTE)nloopOdd - 6) & 0xf)), 4);
		v2 = v5 + v11;
		v12 = rol(*(int *)(pTempCheck + 1) + ((v5 + v11) ^ v5 ^ v3) + v4 + *(DWORD *)(pTempName + 4 * ((nloopOdd - 3) & 0xf)), 11);
		v4 = v2 + v12;
		v13 = rol(*(int *)(pTempCheck + 2) + (v2 ^ v5 ^ (v2 + v12)) + v3 + *(DWORD *)(pTempName + 4 * ((nloopOdd) & 0xf)), 16);
		v3 = v4 + v13;
		v36 = v3 ^ v4;
		v5 = v4 + v13 + rol(*(int *)(pTempCheck + 3) + (v2 ^ v36) + v5 + *(DWORD *)(pTempName + 4 * ((nloopOdd + 3) & 0xf)), 23);
		pTempCheck += 4;
		nloopOdd -= 4;
		if (i == 3)
			break;
		v10 = v36;
	}

	pTempCheck = (int*)vCheckPreLoop4;
	nloopOdd = -2;
	for (int i = 0; i < 4; i++) // 4 times
	{
		v14 = rol(*(int *)(pTempCheck)+(v3 ^ (v5 | ~v4)) + v2 + *(DWORD *)(pTempName + 4 * ((nloopOdd + 2) & 0xf)), 6);
		v2 = v5 + v14;
		v15 = rol(*(int *)(pTempCheck + 1) + (v5 ^ ((v5 + v14) | ~v3)) + v4 + *(DWORD *)(pTempName + 4 * ((nloopOdd - 7) & 0xf)), 10);
		v4 = v2 + v15;
		v16 = rol(*(int *)(pTempCheck + 2) + (v2 ^ ((v2 + v15) | ~v5)) + v3 + *(DWORD *)(pTempName + 4 * ((nloopOdd) & 0xf)), 15);
		v3 = v4 + v16;
		v5 = v3 + rol(*(int *)(pTempCheck + 3) + (v4 ^ ((v4 + v16) | ~v2)) + v5 + *(DWORD *)(pTempName + 4 * ((nloopOdd + 7) & 0xf)), 21);
		pTempCheck += 4;
		nloopOdd -= 4;
	}

	result = existCode;
	v18 = *(DWORD *)(existCode + 8);
	v19 = v2 + *(DWORD *)existCode;
	v20 = *(DWORD *)(existCode + 4);
	*(DWORD *)existCode = v19;
	v21 = *(DWORD *)(existCode + 12);
	*(DWORD *)(existCode + 4) = v5 + v20;
	*(DWORD *)(existCode + 8) = v3 + v18;
	*(DWORD *)(existCode + 12) = v4 + v21;
	return result;
}

int SecondEnCode(int nCheckCode, int nextNum)
{
	unsigned __int64* pUnCheck, nTemp64;
	unsigned int *pLowerTemp, *pHighTemp;
	pUnCheck = (unsigned __int64*)nCheckCode;
	pLowerTemp = (unsigned int*)(&nTemp64);
	pHighTemp = (unsigned int*)(&nTemp64) + 1;

	for (int i = 0; i < nextNum; i++)
	{
		// 首先替换位置
		*pUnCheck = rol64(*pUnCheck, 1);

		nTemp64 = *pUnCheck & 0x4;
		nTemp64 = rol64(nTemp64, 0xB);
		*pLowerTemp ^= (*(unsigned int*)pUnCheck & 0x2000);
		nTemp64 = rol64(nTemp64, 0x12);
		*pLowerTemp ^= (*(unsigned int*)pUnCheck & 0x80000000);
		nTemp64 = rol64(nTemp64, 0x1);
		*pUnCheck ^= nTemp64;
	}
	return nCheckCode;
}

int SecondDeCode(int nCheckCode, int nextNum)
{
	unsigned __int64* pCheckCode, nTemp64;
	unsigned int *pLowerTemp, *pHighTemp;
	pCheckCode = (unsigned __int64*)nCheckCode;
	pLowerTemp = (unsigned int*)(&nTemp64);
	pHighTemp = (unsigned int*)(&nTemp64) + 1;

	for (int i = 0; i < nextNum; i++)
	{
		// 计算相同的 nTemp;
		nTemp64 = *pCheckCode & 0x4;
		nTemp64 = rol64(nTemp64, 0xB);
		*pLowerTemp ^= (*(unsigned int*)pCheckCode & 0x2000);
		nTemp64 = rol64(nTemp64, 0x12);
		*pLowerTemp ^= (*(unsigned int*)pCheckCode & 0x80000000);
		nTemp64 = rol64(nTemp64, 0x1);

		// 异或获得上个移位后的checkcode
		*pCheckCode ^= nTemp64;
		*pCheckCode = ror64(*pCheckCode, 1);
	}

	return nCheckCode;
}

void main()
{
	// unsigned nCode = 0x80;
	char szNameCode[0x40] = { 0 }, szRev[0x40] = { 0 };
	
	const char szName[] = "52pojie.cn";
	memset(szNameCode, 0, 0x40);
	memset(szRev, 0, 0x40);
	strcpy(szNameCode, szName);
	
	cout << "Please insert your name: " << endl;
	cin >> szNameCode;
	strcpy(szRev, szNameCode);
	_strrev(szRev);
	for (int i = 0; i < 3; i++)
	{
		strcpy(szNameCode + strlen(szNameCode), szRev);
	}

	int nNameCodeLen = strlen(szNameCode);
	*((byte*)szNameCode + nNameCodeLen) = 0x80;
	*((unsigned int*)(szNameCode + 0x38)) = 8 * (nNameCodeLen + 1);
	byte szCheckCode[] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10 };
	byte szKeyCode[] = { 0x23, 0x01, 0x00, 0x00, 0x23, 0x01, 0x00, 0x00, 0x23, 0x01, 0x00, 0x00, 0x23, 0x01, 0x00, 0x00 };
	firstEnCode((int *)szNameCode, (int)szCheckCode);
	*(DWORD*)szCheckCode &= 0xffff;
	for (int i = 0; i < 3; i++)
	{
		int nNum = 0xBADC0DE / (0x52 - i);
		SecondDeCode((int)(szCheckCode + 8 - i * 4), nNum);
	}
	
	string strSerial = "";
	for (int i = 0; i < 4; i++)
	{
		DWORD dwCode = *(DWORD*)(szCheckCode + 4 * i);
		char szInfo[16];
		strSerial += itoa(dwCode, szInfo, 16);
		strSerial += " ";
	}
	cout << strSerial << endl;
}