#include <iostream>
using namespace std;

char *name;
unsigned long serial = 0xF6EEDB88;

void main()
{
    unsigned long *p;
    name = new char[30];
    memset(name, 0, 30);
    cout << "enter name:\n";
    strcpy(name, "52pojie.cn");
    // gets_s(name, strlen(name)-1);
    for (int x = 0x10 - 1; x >= 0; x--)
    {
        p = (unsigned long *)&name[x];
        serial = serial ^ *p;
        serial--;
    }
    cout << "serial is: " << serial << endl;
    // system("pause");
}

void memory_dump(void *ptr, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        if (i % 8 == 0 && i != 0)
            printf(" ");
        if (i % 16 == 0 && i != 0)
            printf("\n");
        printf("%02x ", *((uint8_t *)ptr + i));
    }
    printf("\n");
}