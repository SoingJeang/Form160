
#include<iostream>
 
using namespace std;
void main()
{
    char _AL;
    int nHexNum = 9, tempSign, tempUnSign;
    tempSign = (nHexNum & 0xF);
    tempUnSign = (nHexNum & 0xFu);

    _AL = tempSign - ((tempUnSign < 0xA) + 105);
    __asm {
        mov al,_AL 
        das
        mov _AL,al
    }
    printf("%c", _AL);

    system("pause");
}
