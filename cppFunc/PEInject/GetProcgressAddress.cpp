#include "PE.h"

using namespace std;

FARPROC GetProcgressAddress(LPCTSTR lpName)
{
    #ifdef UNICODE
    string fileName = UnicodeToAnsi(lpName);
#else
    string fileName = lpName;
#endif
    tuple<bool, char*, fstream::pos_type> bin = PE::OpenBinary(fileName);
    char *pPeFile = get<1>(bin);
    auto parsedPe = PE::ParsePE(pPeFile);
    
    return NULL;
}