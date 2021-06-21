/*
 * @Author: Soingjeang
 * @Date: 2021-06-21 17:36:51
 * @LastEditors: SoingJeang
 * @LastEditTime: 2021-06-21 19:41:29
 * @FilePath: \Form160\cppFunc\90~100\92.cpp
 */

void NumChange(int *pInsEnum, int *plPara, int *prPara)
{
    int nlpara， nrpara;
    int *pLast = pInsEnum + 16; //68
    nlpara = *plPara;
    nrpara = *prPara;

    for (int i = 0; i<16; i++)
    {
        itn nTemp = *pLast ^ nlpara;
        nlpara = = GetExactNum(pInsEnum, nTemp);
        --pLast;
        nrpara = nTemp;
    }

    *plPara = nrpara ^ *(pInsEnum);
    *prPara = nlpara ^ *(pInsEnum + 1);
}

int GetExactNum(int *pInsEnum, int nPara)
{
    return (*(pInsEnum + nPara + 3144) + *(pInsEnum + nPara >> 8 + 2120)) ^ (*(pInsEnum + nPara >> 16 + 1096) + *(pInsEnum + nPara >> 24 + 72));
}

void EncodeMain(unsigned long *pbase, unsigned int *pszBuff, signed int nlen)
{
    int mem_6198 = 0x00406198;
    int mem_6150 = 0x00406150;
    int nIndex = 0;
    memcpy_s(pbase + 0x12, 0x1000, mem_6198, 0x1000); //复制 00406198内存数据0x1000字节，无变动

    for (int i = 0; i < 18; i++)
    {
        int nXorAdd = 0;
        for (int j = 4; j > 0; j--)
        {
            nXorAdd = *(pszBuff + nIndex) | (nXorAdd << 8);
            nIndex++;
            if (nIndex >= nlen)
                nIndex = 0;
        }
        pbase[x] = *(mem_6150) ^ nXorAdd;
    }
    
    int nRightPara = 0;
    for (int i = 0; i < 9; i++) // 9 * 2 * 4 = 72
    {
        NumChange(pbase, &nLen, &nRightPara);
        pbase[i*2] = nLen;
        pbase[i*2 + 1] = nRightPara;
    }

    for (int i = 0; i < 4; i++) // 4 * 128 * 2 * 4 = 72
    {
        for (int j = 128; j > 0; j--)
        {
            NumChange(pbase, &nLen, &nRightPara);
            pbase[i*128 + j*2 - 1] = nLen;
            pbase[i*128 + j*2] = nRightPara;
        }
    }
}

void main()
{
    unsigned char base_key[] ="94940361391";
    unsigned char base_key_CGG[] = "ChinaCrackingGroup";
    unsigned char base_key_CFF[] = "CrackingForFun";
    unsigned long key1 = 0x11111111;//测试用
    unsigned long key2 = 0x22222222;//测试用
    unsigned char base_key1[] = "fishblow";
    unsigned char* the_key =new unsigned char[260];
    unsigned long * k1 = &key1;  //测试用，可改变指针
    unsigned long * k2 = &key2;  //测试用，可改变指针
        
    unsigned long org_k1 = 0x776F6C62;  //"blow";
    unsigned long org_k2 = 0x68736966;  //"fish"
    LPTSTR  user_key = new TCHAR[16];  //wsprintf 函数缓冲区
    memset(the_key, 0, 260);
    getReg((char *)the_key);
    if (strlen((char *)the_key) == 0)
            the_key = base_key;            //注册表获取ProductID失败则采用默认："94940361391";
    cout << "01--key word is : " << the_key << endl;
    unsigned long  * buf_8980 = new unsigned long[0x1000/4 + 0x12];   //分配加密数据表空间
    memset(buf_8980, 0, 0x1000 + 0x20);                           //填零

    sub_401130(buf_8980, the_key, strlen((char *)the_key));     //第一次初始化加密数据表
    sub_401070(buf_8980, &org_k1, &org_k2);   //加密字符："fish"   "blow";

    wsprintf(user_key, "%08lX%08lX", org_k1, org_k2);  //输出结果为：界面上的 computer ID

    cout << "your computer ID:" << user_key << endl;

    the_key = base_key_CGG;   //"ChinaCrackingGroup";
    cout << "02--key word is : " << the_key << endl;
    sub_401130(buf_8980, the_key, strlen((const char *)the_key));   //第二次初始化加密数据表
    sub_401070(buf_8980, &org_k1, &org_k2);        //加密字符 “第一次结果”

    wsprintf(user_key, "%08lX%08lX", org_k1,org_k2);
    cout <<"key code is:" <<user_key << endl;

        
    the_key = base_key_CFF;    // "CrackingForFun"
    cout << "03--key word is : " << the_key << endl;
    sub_401130(buf_8980, the_key, strlen((const char *)the_key));   //第三次初始化加密数据表

    //int x2 = sub_401000(buf_8980, key1);
    k1 = &org_k1; k2 = &org_k2;  //改变指针，指向内存中正确KEY比较值
    cout << "input code is : " <<hex<<uppercase<< *k1 << *k2 << endl;
    crack_4010D0(buf_8980, k1, k2);  //解密得到用户应该输入的Unlock Code!!
    //sub_4010D0(buf_8980, k1, k2);  //对输入的KEY进行正常加密后判断是否正确
    cout << hex << "Unlock Code is:" << uppercase << "  " << *k1  << *k2 << "   " << endl;
    cout<<"auto head...hello!"<<endl;
    system("pause");
}