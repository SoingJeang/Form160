/*
 * @Author: Soingjeang
 * @Date: 2021-06-08 15:27:38
 * @LastEditors: SoingJeang
 * @LastEditTime: 2021-06-09 16:44:35
 * @FilePath: \cppFunc\121~130\122.cpp
 */
#include <iostream>
#include "common.h"

void GetInputAndSerial(int *pSerialId, int *pInput)
{
    int64_t nSerialInfo = 0xF42C34FF;
    *pSerialId = 0xF42C34FF;
    *pInput = 0;

    *(unsigned *)pSerialId = (unsigned)nSerialInfo;
    char szScan[16], szCon[16] = {0}, szAnsi[4] = {0};
    printf("enter string .string much than 8 cha\n");
    scanf("%s", szScan);
    while(strlen(szScan) < 8)
    {
        printf("string much than 8 cha\n");
        scanf("%s", szScan);
    }

    for(int i = 0; i < 3; i++)
    {
        sprintf(szAnsi, "%d", szScan[i + 1]);
        strcat(szCon, szAnsi);
    }
    szCon[3] = '\0';
    *pInput = atoi(szCon);
}

void CheckCode(int nSerialxCode, int nInputxCode, int* pCheckCode)
{
    if (NULL == pCheckCode)
        return;
    *pCheckCode = 0;

    nInputxCode = ((nInputxCode * 2 + 0x10) * 18) ^ 0x5;
    nSerialxCode = (int)((unsigned)((int)(logic_left((unsigned)nSerialxCode, 2)) / 3) ^ 3) + 0x40;

    nInputxCode = (shift_arithmetic_right(nInputxCode * 6, 1) + 0xd) * 0x36;
    nInputxCode = (nInputxCode + circular_shift_left((unsigned)nInputxCode, 5)) ^ 0x10;
    nSerialxCode = ((unsigned)((nSerialxCode * 6) / 5) ^ 0x25) + 0x27;

    nInputxCode = ((nInputxCode * 2 + 0xd) * 6 * 0x59) ^ 0x9; 
    nSerialxCode = ((nSerialxCode * 5) ^ 0x22) + 0x3;

    _asm{
        mov eax, nInputxCode
        sar eax, 1
        jns CODEBACK
        adc eax,0
CODEBACK:
        mov nInputxCode, eax
    }
    nInputxCode = ((nInputxCode + 0x10) * 3)  ^ 0x6;
    nSerialxCode = ((int)(nSerialxCode * 0x2b / 3) ^ 0x3) + 0x22;

    nInputxCode = shift_arithmetic_right(nInputxCode, 1) + 1;
    nInputxCode = logic_left(nInputxCode * 6, 3) ^ 6;
    nSerialxCode = (shift_arithmetic_right(nSerialxCode * 3, 2) ^ 0x22) + 0x4;

    nSerialxCode = nSerialxCode * 3;

    nInputxCode = ((nInputxCode ^ 2) * 6);
    nSerialxCode = logic_left(nSerialxCode, 2) + 0x4;
    
    *pCheckCode = nInputxCode + nSerialxCode;
}

void main()
{
    int nSerialxCode, nInputxCode, nCheckCode;
    GetInputAndSerial(&nSerialxCode, &nInputxCode);
    CheckCode(nSerialxCode, nInputxCode, &nCheckCode); 
    char szOut[MAX_PATH] = {0};
    sprintf(szOut, "check code:   %d\n", nCheckCode);
    printf(szOut);
}

