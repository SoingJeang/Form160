#include<iostream>
 
using namespace std;
void main()
{
        unsigned char * buff;    //字符串缓冲区
        unsigned long key;  //保存代码校验部分可以通过的值
        unsigned long  nameValue; 
        unsigned long keyHight; //高位
        unsigned long keyLow;
        char * youname; //用户名
        unsigned long serial_No;  //序列号
        unsigned char data[0x3E*4+1] = { 0x55, 0x8B, 0xEC, 0x83, 0xC4, 0xFC, 0x8B, 0x45, 0x0C, 0x83, 0xF8, 0x10, 0x75, 0x0D, 0x6A, 0x00, 0xE8, 0x6B, 0x02, 0x00, 0x00, 0x33, 0xC0, 0xC9,
        0xC2, 0x10, 0x00, 0x83, 0xF8, 0x0F, 0x75, 0x0E, 0x8B, 0x45, 0x08, 0xE8, 0x18, 0x01, 0x00, 0x00, 0x33, 0xC0, 0xC9, 0xC2, 0x10, 0x00, 0x83, 0xF8,
        0x01, 0x75, 0x06, 0x33, 0xC0, 0xC9, 0xC2, 0x10, 0x00, 0x3D, 0x11, 0x01, 0x00, 0x00, 0x0F, 0x85, 0xE7, 0x00, 0x00, 0x00, 0x8B, 0x45, 0x14, 0x3B,
        0x05, 0x60, 0x31, 0x40, 0x00, 0x75, 0x1A, 0x6A, 0x00, 0x68, 0x96, 0x30, 0x40, 0x00, 0x68, 0xA7, 0x30, 0x40, 0x00, 0xFF, 0x75, 0x08, 0xE8, 0x17,
        0x02, 0x00, 0x00, 0x33, 0xC0, 0xC9, 0xC2, 0x10, 0x00, 0x3B, 0x05, 0x58, 0x31, 0x40, 0x00, 0x74, 0x0C, 0x3B, 0x05, 0x54, 0x31, 0x40, 0x00, 0x0F,
        0x85, 0xAE, 0x00, 0x00, 0x00, 0xC7, 0x05, 0xD9, 0x12, 0x40, 0x00, 0x54, 0x45, 0x58, 0x00, 0x6A, 0x00, 0x8D, 0x45, 0xFC, 0x50, 0x6A, 0x64, 0xFF,
        0x35, 0x50, 0x31, 0x40, 0x00, 0xE8, 0xBC, 0x01, 0x00, 0x00, 0x83, 0x7D, 0xFC, 0x00, 0x74, 0x5F, 0x50, 0x6A, 0x14, 0x68, 0x6C, 0x31, 0x40, 0x00,
        0xFF, 0x35, 0x54, 0x31, 0x40, 0x00, 0xE8, 0xAF, 0x01, 0x00, 0x00, 0x85, 0xC0, 0x74, 0x48, 0xA1, 0x0B, 0x30, 0x40, 0x00, 0xBB, 0x6C, 0x31, 0x40,
        0x00, 0x03, 0x03, 0x43, 0x81, 0xFB, 0x7C, 0x31, 0x40, 0x00, 0x75, 0xF5, 0x5B, 0x03, 0xC3, 0x31, 0x05, 0xD9, 0x12, 0x40, 0x00, 0xC1, 0xE8, 0x10,
        0x66, 0x29, 0x05, 0xD9, 0x12, 0x40, 0x00, 0xBE, 0xEC, 0x11, 0x40, 0x00, 0xB9, 0x3E, 0x00, 0x00, 0x00, 0x33, 0xDB, 0xEB, 0x04, 0x00, 0x00, 0x00,
        0x00, 0xAD, 0x33, 0xD8, 0x49, 0x75, 0xFA, 0x81,0 };
 
 

        key = 0xAFFCCFFB; //初始化为最终判断值  0xAFFCCFFB
        buff = data;
        serial_No = 0;
        youname = new char[250];
        memset(youname, 0, 250);
        for (int x = 0; x < 0x3E * 4; x += 4)  //循环读入代码并与最终校验值异或累计
        {
                key = key ^ *(unsigned long *)&buff[x];
                //cout << 0x3E - x / 4 << " key is:" << hex << key << "    (" << *(unsigned long *)&buff[x] << ")" << endl;
        }
        key = (key << 24) + (key >> 8); //调整字节顺序
        cout << "最终校验值:" << hex << key << endl;
        cout << "enter name:";
        strcpy(youname, "123");
        nameValue = 0x58455443;      // 计算name值累加          0x58455443;//"CTEX";
        unsigned long *t1=0; 
        for (int x =0 ; x < 0x10; x++)
        {
                t1 = (unsigned long *)&youname[x];
                nameValue = nameValue + *t1;
        }
        keyHight = key >> 16;      //取出高位
        keyLow = key & 0x0000ffff;  //取出低位
        keyLow = keyLow +( keyHight^0x58);
        key = (keyHight << 16) + keyLow;
        key = key ^ 0x584554;                        //584554("CTE")
        serial_No = key - (nameValue);
                
        cout << "you key is:" << dec << serial_No << endl;
        buff = NULL;
        if (youname != NULL)
                delete[] youname;
        youname = NULL;
        system("pause");
}