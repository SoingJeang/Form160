#include "peInject.h"
#include "PE.h"

using namespace std;
#pragma comment (lib, "user32.lib")

#define CODE_LENGTH 22
BYTE g_bOrder[CODE_LENGTH] = {  0x6A,0x00,     //push 0 
                                0x6A,0x00,     //push 0 
                                0xB8,0x00,0x00,0x00,0x00,  //mov eax,[message]
                                0x50,                      //push eax
                                0x6A,0x00,                 //push 0
                                0xE8,0x00,0x00,0x00,0x00,
                                0xE9,0x00,0x00,0x00,0x00};
BYTE g_bOldCode[CODE_LENGTH];

FARPROC GetEntryAddressFromExe(LPCTSTR lpName)
{
    DWORD dwNumofSection, dwSizeofOptionHeader, dwImageBase, dwEntryCode;
    HANDLE hFile, hMapping;
    void * basepointer = NULL;
    
#ifdef UNICODE
    string fileName = UnicodeToAnsi(lpName);
#else
    string fileName = lpName;
#endif
    tuple<bool, char*, fstream::pos_type> bin = PE::OpenBinary(fileName);

    PIMAGE_DOS_HEADER dos_head = (IMAGE_DOS_HEADER*)get<1>(bin);
    PIMAGE_NT_HEADERS nt = (PIMAGE_NT_HEADERS)((char*)dos_head + dos_head->e_lfanew);

    PIMAGE_OPTIONAL_HEADER option_header = (PIMAGE_OPTIONAL_HEADER)(&(nt->OptionalHeader));
    PIMAGE_FILE_HEADER file_header  = (PIMAGE_FILE_HEADER)(&(nt->FileHeader));
    dwSizeofOptionHeader = file_header->SizeOfOptionalHeader;
    PIMAGE_SECTION_HEADER section_header = (PIMAGE_SECTION_HEADER)((char*)option_header + dwSizeofOptionHeader);
    dwNumofSection = file_header->NumberOfSections;

    dwImageBase = option_header->ImageBase;
    dwEntryCode = option_header->AddressOfEntryPoint + dwImageBase;
    return (FARPROC)dwEntryCode;
}

BOOL GetWriteAddress(LPCTSTR lpName, DWORD dwMyFuncAddress, DWORD* pdwNewEntryAddress, DWORD* pdwWriteAddress, DWORD *pdwCallShift, DWORD *pdwOrderAddress)
{
    DWORD dwNumofSection, dwSizeofOptionHeader, dwImageBase, dwEntryCode, dwUnInitDataSize,
          dwPointerRawData, dwVirtualAddress, dwCodeWirteAddress;
    HANDLE hFile, hMapping;
#ifdef UNICODE
    string fileName = UnicodeToAnsi(lpName);
#else
    string fileName = lpName;
#endif
    tuple<bool, char*, fstream::pos_type> bin = PE::OpenBinary(fileName);

    PIMAGE_DOS_HEADER dos_head = (IMAGE_DOS_HEADER*)get<1>(bin);
    PIMAGE_NT_HEADERS nt = (PIMAGE_NT_HEADERS)((char*)dos_head + dos_head->e_lfanew);
    PIMAGE_OPTIONAL_HEADER option_header = (PIMAGE_OPTIONAL_HEADER)(&(nt->OptionalHeader));
    PIMAGE_FILE_HEADER file_header  = (PIMAGE_FILE_HEADER)(&(nt->FileHeader));
    dwSizeofOptionHeader = file_header->SizeOfOptionalHeader;
    PIMAGE_SECTION_HEADER section_header = (PIMAGE_SECTION_HEADER)((char*)option_header + dwSizeofOptionHeader);
    dwNumofSection = file_header->NumberOfSections;

    dwImageBase = option_header->ImageBase;
    dwEntryCode = option_header->AddressOfEntryPoint + dwImageBase;
    DWORD Charac = IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ;
    for (int i = dwNumofSection - 1; i >= 0; i--)
    {
        if(section_header->SizeOfRawData > 0 && (section_header->Characteristics & Charac))
            break;
        section_header = (PIMAGE_SECTION_HEADER)((char*)section_header + 40);
    }
    dwUnInitDataSize = section_header->Misc.VirtualSize;
    dwPointerRawData = section_header->PointerToRawData;
    dwVirtualAddress = section_header->VirtualAddress;
    dwCodeWirteAddress = dwUnInitDataSize + dwPointerRawData;
    // HMODULE hModule = LoadLibraryA("user32.dll");
    // MessageboxAAddress = (ULONGLONG)GetProcAddress(hModule, "MessageBoxA");
    //计算CALL 偏移：跳转地址 = 当前地址+5+x   ->x = 跳转地址 -当前地址-5
    *pdwNewEntryAddress = dwVirtualAddress+ dwUnInitDataSize;
    *pdwWriteAddress = dwUnInitDataSize + dwPointerRawData;
    *pdwCallShift = dwMyFuncAddress - (dwImageBase + dwVirtualAddress + dwUnInitDataSize + 5);
    *pdwOrderAddress = dwUnInitDataSize + dwImageBase + dwVirtualAddress;

    return TRUE;
}

BOOL InjectToPe(LPCTSTR lpName, LPCTSTR lpNewFileName)
{  
    DWORD MessageboxAAddress = 0, dwNewEnter, dwWriteAddress, dwCallShift, dwOrderAddress;
    void * basepointer = NULL;
    HANDLE hFile, hMapping;
    HMODULE hModule = LoadLibraryA("user32.dll");
    MessageboxAAddress = (ULONGLONG)GetProcAddress(hModule, "MessageBoxA");

    if(!GetWriteAddress(lpName, MessageboxAAddress, &dwNewEnter, &dwWriteAddress, &dwCallShift, &dwOrderAddress))
        return FALSE;
    
#ifdef UNICODE
    string fileName = UnicodeToAnsi(lpName);
    string fileNewName = UnicodeToAnsi(lpNewFileName);
#else
    string fileName = lpName;
    string fileNewName = lpNewFileName;
#endif
    tuple<bool, char*, fstream::pos_type> bin = PE::OpenBinary(fileName);

    PIMAGE_DOS_HEADER dos_head = (IMAGE_DOS_HEADER*)get<1>(bin);
    PIMAGE_NT_HEADERS nt = (PIMAGE_NT_HEADERS)((char*)dos_head + dos_head->e_lfanew);
    PIMAGE_OPTIONAL_HEADER option_header = (PIMAGE_OPTIONAL_HEADER)(&(nt->OptionalHeader));

    // 去地址随机化
    //将代码写入到 文件中
    option_header->DllCharacteristics = 0x8100;
    memcpy((PBYTE)dos_head + dwWriteAddress, g_bOrder, CODE_LENGTH);
    // 将要写入的输出字符写到 文件空空间中
    char message[] = "Hooked";
    memcpy((PBYTE)dos_head + dwWriteAddress + CODE_LENGTH, message, sizeof(message));
    memcpy((PBYTE)dos_head + dwWriteAddress + 13, &dwCallShift, 4);
    DWORD dwParamMess = dwOrderAddress + CODE_LENGTH;
    memcpy((PBYTE)dos_head + dwWriteAddress + 5, &dwParamMess, 4);
    DWORD dwOriginEntryAddress = option_header->AddressOfEntryPoint + option_header->ImageBase - (dwOrderAddress + CODE_LENGTH);
    memcpy((PBYTE)dos_head + dwWriteAddress + 18, &dwOriginEntryAddress, 4);
    //修改入口地址
    option_header->AddressOfEntryPoint = dwNewEnter;
    FILE* fpp = NULL;
    if(0 != fopen_s(&fpp, fileNewName.c_str(), "wb+"))
        return FALSE;
    
    printf("%x\n",_msize((char*)dos_head));
    fwrite((PBYTE)dos_head, sizeof(char), get<2>(bin), fpp);
    fflush(fpp);
    fclose(fpp);
    return TRUE;
}