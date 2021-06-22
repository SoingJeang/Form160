/*
 * @Author: Soingjeang
 * @Date: 2021-06-14 14:08:35
 * @LastEditors: SoingJeang
 * @LastEditTime: 2021-06-19 17:33:00
 * @FilePath: /cppFunc/121~130/125.cpp
 */

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void fGetFilePosition(string strName, string strCompany, int* pFilePos, int *pFileLen)
{
    int nNameLen, nCompanyLen;
    nNameLen = strName.length();
    nCompanyLen = strCompany.length()
    listName = list(strName)
    listCompany = list(strCompany)
    nLenLoop = 1
    
    for i in range(nameLen):
        nLenLoop = nLenLoop * (i + ord(listName[i]) - companyLen)
        if (nLenLoop > 0):
            nLenLoop &= 0xffffffff
    
    nFileLenth = listPos[0]
    nReadSize = ((nFileLenth << 8) ^ nLenLoop) & 0xffffffff
    nTemp = nFileLenth >> 1

    if (nReadSize % nTemp == 0):
        nReadSize ^= 0xfffffff

    # if nReadSize & 0x8fffffff:
    #     nReadSize = -1 * ((nReadSize ^ 0xfffffff) + 1)
        
    result = nReadSize % nTemp
    listPos.append(result)
    listPos[0] = (nFileLenth - result) >> 1
}

void fFileRead(char *pFilenName, char *pBuffer,  int nBegin, int *pReadSize)
{
    ifstream fFile;
    fFile.open("125.exe", ios::binary);
    if (!fFile.is_open())
    {
        cout << "open err";
        return;
    }

    size_t i, nSize = *pReadSize;
    for (i = 0; i < nSize; i+=1024)
    {
        fFile.read(pBuffer + i, 1024);
    }
    fFile.read(pBuffer + i, nSize - i);
    *pReadSize = strlen(pBuffer);
}

void fRead(char *pBuffer, int nBegin, int *pReadSize)
{
    
}

void fMemoryChang(char *pBuffer, int nSize, string strName)
{
    int nNameLen = strName.size(), nXorCode, nRolSize, nIndex = 0;
    char *pNameCopy = new char[nNameLen + 3];
    memset(pNameCopy, 0, nNameLen + 3);
    memcpy(pNameCopy, strName.c_str(), nNameLen);
    
    nIndex = 0;
    while (nIndex + 3 < nNameLen)
    {
        nXorCode = *((int *)pNameCopy);
        nXorCode ^= *((int *)(pBuffer + nIndex));
        nXorCode ^= nIndex;
        nRolSize = nXorCode % 0x1f;
        int nCodeSingle = nXorCode << nRolSize;
        if (nCodeSingle < 0)
        {
            nCodeSingle = ~nCodeSingle;
        }
        memcpy(pBuffer + nIndex, &nCodeSingle, sizeof(int));

        nIndex + 4;
    }
    

    if (NULL != pNameCopy)
    {
        delete []pNameCopy;
        pNameCopy = NULL;
    }
}

void fLevelFive()
{
    string strName, strCompany, strCheckCode;    
    cout << "please ipput your name:\n";
    strName = "12345678";
    strCompany = "company";
    // cin >> strName;
    // cin >> strCompany;
    int nFilePos, nFileSize;
    fGetFilePosition(&nFilePos, &nFileSize);
    char *pBuffer = new char[nFileSize + 4];
    fRead(pBuffer, nFilePos, &nFileSize);
    fMemoryChang(pBuffer, nFileSize, strName);
    
    if (pBuffer != NULL)
    {
        delete []pBuffer;
        pBuffer = NULL;
    }
    
}

int main()
{
    fLevelFive();
    return 0;
}