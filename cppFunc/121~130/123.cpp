/*
 * @Author: Soingjeang
 * @Date: 2021-06-10 12:13:43
 * @LastEditors: SoingJeang
 * @LastEditTime: 2021-06-10 13:22:28
 * @FilePath: \cppFunc\121~130\123.cpp
 */
#include <string>
#include <iostream>

int main(void)
{
    char tmp[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char serial[20] = "TSSFTMEZDPKS";

    unsigned long i = 692659380;
    while (true)
    {
        srand(i);
        std::string str = "";
        for (int j = 0; j < 12; j++)
        {
            int b = rand();
            b %= 26;
            str += tmp[b];
        }
        if (!strcmp(serial, str.c_str()))
        {
            break;
        }
        i++;
    }
    
    std::cout << i << std::endl;
}