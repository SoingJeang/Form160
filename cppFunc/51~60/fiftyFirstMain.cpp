/*
 * @Author: Soingjeang
 * @Date: 2021-03-26 12:10:53
 * @LastEditors: SoingJeang
 * @LastEditTime: 2021-03-26 15:22:44
 * @FilePath: \cppFunc\51~60\fiftyFirstMain.cpp
 */
#include <iostream>

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


std::string Hex2Char(unsigned int unHexNum)
{
    std::string strRet = "";
    unsigned int nTemp = unHexNum;
    while(nTemp > 0)
    {
        char c = nTemp & 0xff;
        strRet += c;
        nTemp /= 0x100;
    }
    return strRet;
}


void main()
{
    unsigned int nblockCheckPre = 0x36455544;
    unsigned int nblockCodePre = 0x4071885;
    unsigned int nblockCheckAfter = 0x43534952;
    unsigned int nblockCodeAfter = 0x4b00d127;
    unsigned int nRolPre = 0, nRolAfter = 0, nTemp;
    std::string strCode = "";
    

    unsigned char al, ah;
    while (true)
    {
        if(nblockCheckPre == nblockCodePre)
        {
            bool bFound = true;
            nTemp = nRolPre;
            while(nTemp > 0)
            {
                if(!((nTemp & 0xff) >= 0x30 && (nTemp & 0xff) <= 0x7E))
                {
                    bFound = false;
                    break;
                }
                nTemp /= 0x100;
            }
            if (bFound)
                break;
        }
            
        if(nRolPre == 0xffffffff)
            break;
        nRolPre ++;
        al = nblockCodePre & 0xff;
        nblockCodePre -= al;
        al = al - nRolPre & 0xff;
        nblockCodePre += al;

        ah = (nblockCodePre & 0xff00)/ 0x100;
        nblockCodePre -= ah * 0x100;
        ah = ah ^ al;
        nblockCodePre += ah * 0x100;
        nblockCodePre = ror(nblockCodePre, 6);
    }
    strCode += Hex2Char(nRolPre);

    while (true)
    {
        if(nblockCheckAfter == nblockCodeAfter)
        {
            bool bFound = true;
            nTemp = nRolAfter;
            while(nTemp > 0)
            {
                if(!((nTemp & 0xff) >= 0x30 && (nTemp & 0xff) <= 0x7E))
                {
                    bFound = false;
                    break;
                }
                nTemp /= 0x100;
            }
            if (bFound)
                break;
        }
        
        if(nRolAfter == 0xffffffff)
            break;
        nRolAfter ++;
        al = nblockCodeAfter & 0xff;
        nblockCodeAfter -= al;
        al = al - nRolAfter & 0xff;
        nblockCodeAfter += al;

        ah = (nblockCodeAfter & 0xff00)/ 0x100;
        nblockCodeAfter -= ah * 0x100;
        ah = ah ^ al;
        nblockCodeAfter += ah * 0x100;
        nblockCodeAfter = ror(nblockCodeAfter, 6);
    }
    strCode += Hex2Char(nRolAfter);
    
    std::cout << strCode;
}