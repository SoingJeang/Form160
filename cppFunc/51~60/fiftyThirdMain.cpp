/*
 * @Author: Soingjeang
 * @Date: 2021-04-07 10:37:04
 * @LastEditors: SoingJeang
 * @LastEditTime: 2021-04-09 10:42:39
 * @FilePath: \cppFunc\51~60\fiftyThirdMain.cpp
 */
#include <windows.h>
#include <iostream>
#include <memory.h>

#pragma comment(lib, "Advapi32")

using namespace std;

void memory_dump(void *pAddress, int maxLength)
{
    string result = "";
    const unsigned char * p = reinterpret_cast< const unsigned char *>(pAddress);
    cout << "Memory location: 0x" << hex << (unsigned int)p << endl;
    for (unsigned int i = 0; i < maxLength; i++) {
		if(i % 0x10 == 0)
			cout << "\n";
        cout << hex << int(p[i]) << " ";
    }
}

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

int PositiveNum(int nNum)
{
    int nResult = 0;
    for (; nNum; nNum &= nNum-1)
    {
        nResult++;
    }
    return nResult;
}

DWORD pDwDelta[] = {
		0xBCFEF35, 0x179FDE6B, 0x0C5E7E798, 0x5E7F79AC, 0x0BCFEF359,		// 41c2c0
		0x0F9FDC6B7, 0x73FBAD6A, 0x2F3FBCD6, 0x0E7F75AD5, 0x4FEE95AF,
		0x9FDD2B5E, 0x0FF74CD76, 0x0BFBA76B9, 0x7EE9BAE8, 0x0FDD375D1,
		0x0F74D974E, 0x7BA6CBA7, 0x6E9B0E99, 0x0DD361D32, 0x3A6C1A60,
		0x74D834C0, 0x0E9B06981, 0x5360F306, 0x0A6C1E60C, 0x0CD83EC1D,
		0x1B07F83F, 0x360FF07E, 0x6C1FE0FD, 0x0D83FC1FA, 0x307FA3F0,
		0x60FF47E1, 0x0C1FE8FC2, 0x3FD3F80, 0x0FF4FE02, 0x7FA7F01,
		0x1FE9FC04, 0x3FD3F808, 0x7FA7F010, 0x7E9FE047, 0x0FD3FC08E,
		0x0FF4FE021, 0x0F4FF4232, 0x7A7FA119, 0x0D3FD48C3, 0x27FAB183,
		0x4FF56306, 0x9FEAC60D, 0x69FEA461, 0x0BFD5AC1E, 0x0FFAB7839,
		0x7F56D076, 0x0FEADA0ED, 0x7D5B61DE, 0x0FAB6C3BC, 0x756DA77D,
		0x0EADB4EFA, 0x2DB58F80, 0x5B6B1F00, 0x0B6D63E01, 0x55B6BDF1,
		0x0AB6D7BE3, 0x0D6DAD7C2, 0x5B589808, 0x0EDAC5C06, 

		0x9B4D1349, 0x369A2692, 0x0CDA689A4, 0x0DA689A48, 0x0B4D13490,		// 41c3c0
		0x69A26921, 0x0D344D243, 0x6D344D24, 0x0A689A486, 0x4D13490D,
		0x9A26921A, 0x689A486B, 0x344D2435, 0x0D13490D7, 0x0A26921AE,
		0x89A486BA, 0x44D2435D, 0x13490D75, 0x26921AEA, 0x4D2435D5,
		0x9A486BAA, 0x3490D754, 0x6921AEA9, 0x0D2435D52, 0x0A486BAA5,
		0x490D754B, 0x921AEA96, 0x2435D52C, 0x486BAA58, 0x90D754B1,
		0x21AEA962, 0x435D52C4, 0x86BAA589, 0x1AEA9624, 0x0D754B12,
		0x35D52C48, 0x6BAA5890, 0x0D754B120, 0x5D52C481, 0x0BAA58902,
		0x0AEA96240, 0x0EA96240A, 0x754B1205, 0x0AA58902A, 0x54B12055,
		0x0A96240AA, 0x52C48154, 0x0D52C4815, 0x0A58902A9, 0x4B120553,
		0x96240AA7, 0x2C48154E, 0x58902A9D, 0x0B120553A, 0x6240AA75,
		0x0C48154EA, 0x48154EAB, 0x902A9D56, 0x20553AAC, 0x8902A9D5,
		0x120553AA, 0x240AA755, 0x8154EAB3, 0x40AA7559,

		0x0AE10E7F5, 0x7087FFB6, 0x0E10FFF6D, 0x421FDEDF, 0x843FBDBF,			// 41c4c0
		0x0DC21EFEF, 0x3843FFDB, 0x887F5B7B, 0x90FE96F3, 0x7F45782,
		0x0FE8AF04, 0x0A1FD0DE3, 0x0C3FA3BC3, 0x0FE8AF04F, 0x7D15C09B,
		0x7F457827, 0x1FD15E09, 0x3FA2BC13, 0x0FA2B8136, 0x74572268,
		0x15CA5A45, 0x0C5728693, 0x515CA9A5, 0x0A2B9534B, 0x0AE52D22,
		0x0E8AE44D0, 0x0DCA5845F, 0x394B28BB, 0x72965177, 0x2B94B48B,
		0x57296916, 0x0AE52D22D, 0x0E52CA2EF, 0x4A5965DB, 0x94B2CBB7,
		0x0A965B76A, 0x2596BDA5, 0x4B2D7B4A, 0x965AF695, 0x0ACB5CD2F,
		0x0D96BBA5B, 0x32D754B3, 0x0D2CB4ED0, 0x65AEA967, 0x0CB5D52CE,
		0x2D750B30, 0x16BA8598, 0x5AEA1660, 0x0B5D42CC0, 0x5750D30E,
		0x0AEA1A61D, 0x0DD436C3E, 0x3A86F879, 0x750DF0F2, 0x0EA1BE1E5,
		0x5437E3CF, 0x0EBA87985, 0x21BF7E74, 0x437EFCE8, 0x0A86FC79E,
		0x0D0DFAF38, 0x86FDF9D1, 0x8DFBD3A7, 0x9BF7874A,

		0x0DFCF8EDF, 0x0FE7C76FE, 0x0FCF8EDFC, 0x0F9F1DBF9, 0x0F3E3B7F2,		// 41c5c0
		0x0BF9F1DBF, 0x7F3E3B7F, 0x0E7C76FE5, 0x0CF8EDFCB, 0x7C76FE5F,
		0x0F8EDFCBE, 0x9F1DBF97, 0x3E3B7F2F, 0x8EDFCBE0, 0x1DBF97C1,
		0x0C76FE5F0, 0x0F1DBF97C, 0x0E3B7F2F8, 0x3B7F2F82, 0x76FE5F05,
		0x0BF97C156, 0x6FE5F055, 0x0DBF97C15, 0x0B7F2F82A, 0x0DFCBE0AB,
		0x0EDFCBE0A, 0x0F97C1561, 0x0F2F82AC3, 0x0E5F05586, 0x7F2F82AC,
		0x0FE5F0558, 0x0FCBE0AB0, 0x0CBE0AB0C, 0x97C15619, 0x2F82AC32,
		0x5F055865, 0x7C156197, 0x0F82AC32E, 0x0F055865C, 0x0E0AB0CB9,
		0x0C1561973, 0x82AC32E7, 0x0BE0AB0CB, 0x55865CE, 0x0AB0CB9C,
		0x2AC32E72, 0x15619739, 0x55865CE4, 0x0AB0CB9C8, 0x0AC32E723,
		0x5865CE46, 0x0B0CB9C8D, 0x6197391B, 0x0C32E7236, 0x865CE46C,
		0x0CB9C8D9, 0x56197391, 0x65CE46CB, 0x0CB9C8D96, 0x197391B2,
		0x32E72365, 0x97391B2C, 0x2E723659, 0x5CE46CB3,
	}; // 64 个

int SecondEnCode(int nCheckCode, DWORD *pDeltaPre, DWORD *pDeltaAfter)
{
	int *pCheckCode = (int*)nCheckCode;
	int nFirstCode = 0, nSecondCode = 0;
    
    for (int i = 0; i < 32; i++)
    {
        nFirstCode = nFirstCode << 1;
        if((PositiveNum(*pDeltaAfter & *(pCheckCode + 1)) ^ PositiveNum(*pDeltaPre & *(pCheckCode))) & 1)
            nFirstCode++;
        pDeltaPre++;
        pDeltaAfter++;
    }
    for (int i = 0; i < 32; i++)
    {
        nSecondCode = nSecondCode << 1;
        if((PositiveNum(*pDeltaAfter & *(pCheckCode + 1)) ^ PositiveNum(*pDeltaPre & *(pCheckCode))) & 1)
            nSecondCode++;
        pDeltaPre++;
        pDeltaAfter++;
    }
	*pCheckCode = nFirstCode;
	*(pCheckCode + 1) = nSecondCode;
    
	return nCheckCode;
}

int SecondDeCode(int nCheckCode, DWORD *pDeltaPre, DWORD *pDeltaAfter)
{
	return nCheckCode;
}

void main()
{
	// unsigned nCode = 0x80;
	char szNameCode[0x40] = { 0 }, szRev[0x40] = { 0 }, szOwnname[0x40] = {0};
	const char szName[] = "entername";
	int nCheckInserCode[] = { 1, 2, 3 };
	memset(szNameCode, 0, 0x40);
	memset(szRev, 0, 0x40);
	strcpy(szNameCode, szName);
	
	// cout << "Please insert your name: " << endl;
	// cin >> szNameCode;
	strcpy(szRev, szNameCode);
	_strrev(szRev);
	for (int i = 0; i < 2; i++)
	{
		strcpy(szNameCode + strlen(szNameCode), szRev);
	}
	
	HKEY hKey = NULL;
	DWORD dwType = 1, dwSize;

	if (ERROR_SUCCESS != RegOpenKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", &hKey))
		return;
	if (ERROR_SUCCESS != RegQueryValueExA(hKey, "RegisteredOwner", 0, &dwType, (BYTE*)szOwnname, &dwSize))
		return;
	strcat(szNameCode, szOwnname);

	int nNameCodeLen = strlen(szNameCode);
	*((byte*)szNameCode + nNameCodeLen) = 0x80;
	*((unsigned int*)(szNameCode + 0x38)) = 8 * (nNameCodeLen + 1);
	byte szCheckCode[] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10 };
	firstEnCode((int *)szNameCode, (int)szCheckCode);
	*(DWORD*)szCheckCode &= 0xffff;
	for (int i = 0; i < 2; i++)
	{
		SecondEnCode((int)(nCheckInserCode + i), pDwDelta + (2 * i) * 64, pDwDelta + (2 * i + 1) * 64);
	}
	
	cout << nCheckInserCode << endl;
}