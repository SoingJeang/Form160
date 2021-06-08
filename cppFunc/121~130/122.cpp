/*
 * @Author: Soingjeang
 * @Date: 2021-06-08 15:27:38
 * @LastEditors: SoingJeang
 * @LastEditTime: 2021-06-08 19:14:52
 * @FilePath: \cppFunc\121~130\122.cpp
 */
#include <windows.h>
#include <iostream>
#include "common.h"

void GetInputAndSerial(int *pSerialId, int *pInput)
{
    int64_t nSerialInfo = 0xF42C34FF;
    *pSerialId = 0xF42C34FF;
    *pInput = 989;

    *(unsigned *)pSerialId = (unsigned)nSerialInfo;
    // if(nSerialInfo & 0x80000000)
    //     *pSerialId = -(int)(nSerialInfo ^ 0xffffffff) + 1;
    // else
    //     *pSerialId = (int)nSerialInfo;
}

void CheckCode(int nSerialxCode, int nInputxCode)
{
    char szOut[MAX_PATH] = {0};

    nInputxCode = ((nInputxCode * 2 + 0x10) * 18) ^ 0x5;
    nSerialxCode = (int)(logic_left((unsigned)nSerialxCode, 2)) / 3;
    nSerialxCode = (int)((unsigned)(nSerialxCode) ^ 3) + 0x40;

    nInputxCode = (shift_arithmetic_right(nInputxCode * 6, 1) + 0xd) * 0x36;
    nInputxCode = (nInputxCode + circular_shift_left((unsigned)nInputxCode, 5)) ^ 0x10;
    nSerialxCode = (int)((nSerialxCode * 6) / 5) ^ 0x25 ^ 0x27;

    nInputxCode = ((nInputxCode * 2 + 0xd) * 6 * 0x59) ^ 0x9; 
    nSerialxCode = ((nSerialxCode * 5) ^ 0x22) + 0x3;

    nInputxCode = ((shift_arithmetic_right(nInputxCode, 1) + 0x10) * 3)  ^ 0x6;
    nSerialxCode = ((int)(nSerialxCode * 0x2b / 3) ^ 0x3) + 0x22;

    nInputxCode = logic_left((shift_arithmetic_right((unsigned)nInputxCode, 1) + 1) * 6, 3) ^ 6;
    nSerialxCode = (shift_arithmetic_right(nSerialxCode * 3, 2) ^ 0x22) + 0x4;

    nSerialxCode = nSerialxCode * 3;

    nInputxCode = ((nInputxCode ^ 2) * 6);
    nSerialxCode = logic_left(nSerialxCode, 2) + 0x4;
    
    sprintf(szOut, "serial: %d\ticode: %d\n", nSerialxCode, nInputxCode);
    printf(szOut);
}

void main()
{
    int nSerialxCode, nInputxCode;
    GetInputAndSerial(&nSerialxCode, &nInputxCode);
    CheckCode(nSerialxCode, nInputxCode); 
}

