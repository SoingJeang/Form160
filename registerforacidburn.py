import numpy
import datetime
import random
import struct
import string
import datetime
import math
import hashlib

from numpy.testing._private.utils import check_free_memory
from commonForm import *

def firstFrom160():
    checkname = helloEnter()
    sierailcode = "CW-" + str(ord(checkname[0]) * int(0x29) * 2) + "-CRACKED"
    helloEnd(sierailcode)

def secondFrom160():
    checkname = helloEnter()
    sierailcode = "AKA-" + str(0x17cfb * len(checkname) + ord(checkname[0]))
    helloEnd(sierailcode)

# ((len(name) * 0x15b38 + name[0]) + 2) * 0x408 a-0x40 - 0xc2e
# 800145
def thirdForm160():
    checkname = helloEnter()
    firstcharac = ord(checkname[0])
    sierailfloat = ((len(checkname) * 0x15b38 + firstcharac) + 2) * 0x3 - 0x2 + 15
    helloEnd(str(sierailfloat))

def ForthForm160():
    checkname = helloEnter()
    strSunBird = "黑头Sun Bird"
    strSel = "dseloffc-012-OK"
    checklen = 0
    for _char in checkname:
        if '\u4e00' <= _char <= '\u9fa5':
            checklen += 2
        else:
            checklen += 1

    sierail = strSunBird + str(checklen + 5) + strSel + checkname
    helloEnd(sierail)

def FivthForm160():
    checkname = helloEnter()
    if len(checkname) < 6:
        print("name must than 5 num\n")
        return
    numFive = ord(checkname[4]) % 7 + 2
    numFac = numpy.math.factorial(numFive)
    ebx = 0

    for _char in checkname:
        endchar = numFac * ord(_char)
        ebx = endchar + ebx

    sierail = ebx - 0x7A69
    helloEnd(sierail)
    strCode = str(sierail)
    indexCode = 1
    strNewName = ""
    for _char in strCode:
        newNameSingle = ord(_char) * ord(_char) * indexCode % 0x19 + 0x41
        strNewName += chr(newNameSingle)
        indexCode+=1
    print("Second SerialName: \t" + strNewName)
    print("\n")

def SixSupport(edi, listName):
    lenCode = len(listName)
    ebx = 0
    edx = 0
    for i in range(lenCode):
        for j in range(lenCode):
           edx = ord(listName[i]) * ord(listName[lenCode - j - 1]) * edi
           ebx += edx
    return ebx

def ServenthForm160():
    # 1、虚假code(>5个非全数字) 获得eax 进edi
    checkCode = input("Please Enter Your First Code!\n")
    if(len(checkCode) < 6):
        print("First Code must more than 5 character!\n")
        return
    listCheckCode = list(checkCode)
    totalAdd = 0x37B
    for i in range(len(checkCode) - 1):
        totalAdd += (ord(listCheckCode[i + 1]) % 0x11 + 1) * ord(listCheckCode[i])
    edi = totalAdd % 0x7148

    # 接着输入新的 name 和 code 进行 比对 去除register
    checkName = helloEnter()
    if (len(checkName) < 5):
        print("Check name must more than 4 character!\n")
        return
    ebx = SixSupport(edi, list(checkName)) 
    ecx = ebx % 0xA2C2A
    # ecx = hexCode / 0x59 + hexCode % 0x50 + 1
    # x / a + x % b  + 1 = c
    # ecx = hexCode / 0x59 + index + 1
    # index = hexCode % 0x50
    RetCode = -1
    for i in range(int("0x50", 16)):
        hexCode = (ecx - 1 - i ) * int("0x59", 16)
        for j in range(int("0x59", 16)): #for more than hexCOde to hexCode + 0x59
            if((((hexCode + j) % int("0x50", 16)) == i)):
                RetCode = hexCode + j
                if(-1 != RetCode):
                    break

    if(-1 == RetCode):
        print("Find Code ERror!\n")
        return
    
    helloEnd(RetCode)

    # 2、通过edi获得key 比对
    pass

def NinthForm160():
    checkname = helloEnter()
    charsAdd = 0
    for _char in checkname:
        charsAdd += ord(_char)
    
    charsAdd *= 0x499602D2
    sierail = list(str(charsAdd))
    sierail[3] = '-'
    sierail[8] = '-'
    helloEnd(''.join(sierail))

def TenthForm160():
    checkname = r"kXy^rO|*yXo*m\kMuOn*+"
    checkCode = ""
    for _char in checkname:
        newChar = ord(_char) - 0xA
        checkCode += chr(newChar)
    print(checkCode)

def EleventhForm160():
    #前2个字符
    checkName = r"0817E747D7A7D7C7F82836D74747A7F7E7B7C7D826D817E7B7C"
    lenCheckName = int(len(checkName)/2)
    listCheckName = list(checkName)

    # (10 * a + b) + a + 0x30 = 0x81
    # (10 * a + b) + b + 0x30 = 0x7E

    firstCode = int(listCheckName[1], 16) * 16 + int(listCheckName[2], 16)
    SecondCode = int(listCheckName[3], 16) * 16 + int(listCheckName[4], 16)
    firstNum = int(((firstCode - 0x30) * 2 - (SecondCode - 0x30)) / 12)
    secondNum = int(firstCode - 0x30 - 11 * firstNum)

    keyInter = firstNum * 10 + secondNum
    checkCode = ""
    for i in range(lenCheckName):
        TenNum = int(listCheckName[2*i+1], 16) * 16
        SinNum = int(listCheckName[2*i+2], 16)
        RightNum = TenNum + SinNum
       
        checkCode += chr(RightNum - keyInter)

    print(checkCode)

def ThirdThenForm160():
    var88  = datetime.datetime.now().day * 22 + datetime.datetime.now().month * 1 + datetime.datetime.now().year * 1900
    varStr = str(var88 * 2 + 13 * 1905 +13 * 1905 )
    print("stringFirst:\t" + varStr)
    checkName = helloEnter()

    var_90 = 0.0
    var_178 = 0.0
    strFactor = "0110617121214051216101106141404110614140411091211100810101608040610121608100416"
    indexFac = 1
    listCheckName = list(checkName)
    for i in range(len(checkName)):
        if i < 3:
            continue
        var_90 = ord(listCheckName[i]) * int(strFactor[indexFac*3 - 1: indexFac*3 + 2]) + var_90
        if(i-1  > len(checkName)):
            var_178 = ord(listCheckName[i]) * 0 *  int(strFactor[indexFac*2 - 1: indexFac*2 + 1])+ var_178
        else:
            var_178 = ord(listCheckName[i]) * ord(listCheckName[i-1]) *  int(strFactor[indexFac*2 - 1: indexFac*2 + 1])+ var_178
        indexFac += 1
    checkCode = str(int(var_90)) + "-" + str(int(var_178))
    helloEnd(checkCode) 

def ForteenthForm160():
    checkCode = ""
    for i in range(9):
        checkNum = ((i + 1) ^ 2) % 10
        checkCode += str(checkNum)
    helloEnd(checkCode)

def FifteenForm160():
    pass

def SixteenForm160():
    ForteenthForm160()

def SeventeenForm160():
    numLen = random.randint(5,10)
    firstLen = 0
    while(True):
        checkCode = ""
        for i in range(numLen - 1):
            char = random.randint(0,9)
            if i == 0:
                firstLen = (char + 0x30) * numLen
            firstLen = firstLen - char - 0x30
            checkCode += str(char)
        if (firstLen >= 0x30 and firstLen <= 0x39):
            checkCode += chr(firstLen)
            break
    print(checkCode)
        
def EighteenForm160():
    checkCode = "<BrD-SoB>"
    helloEnd(checkCode)

def NineteenForm160():
    nCheck = 0x81276345
    
    checkName = helloEnter()
    if (len(checkName) < 5):
        print("name must than 4")
        return
        
    nCheckLen = len(checkName)
    nIndex = 0
    for _char in checkName:
        nCheck += ord(_char)
        nCheck ^= (nIndex << 8)
    
        nCheck = (~(nCheckLen * nIndex)) * (nIndex + 1) * nCheck
        nCheck &= 0xffffffff
        nIndex += 1

    helloEnd(nCheck)
            
def twentythForm160():
    checkCode = 0x3E74984B
    EnterNum = checkCode / 3
    helloEnd(int(EnterNum))

def twentyfirstFrom160():
    dicParam1 = {
        "a":0x427, "b":0x6BC, "c":0x491, "d":0x474D, "e":0x400, "f":0x6D0,
        "g":0x67D, "h":0x750, "i":0x43C, "j":0x764, "k":0xC0, "l":0x277D,
        "m":0x81E, "n":0xE07, "o":0x8E, "p":0x9A670, "q":0xD57, "r":0x5FEB,
        "s":0x8B0, "t":0x4BB, "u":0x8C2, "v":0x1CA6, "w":0x395, "x":0x251E,
        "y":0x2D13, "z":0x1900, 
        "A":0x428, "B":0xB1630, "C":0xD86, "D":0x11A4, "E":0x11F0A, "F":0x3CC2,
        "G":0x3E1A8, "H":0x91E4, "I":0x6B42, "J":0x516A4, "K":0x4345A, "L":0x1BFDD9,
        "M":0x286D, "N":0x401, "O":0x674, "P":0x9C, "Q":0x156, "R":0x8627,
        "S":0x748190, "T":0xA568, "U":0x15592, "V":0x1DD9, "W":0x266A, "X":0x3CC0,
        "Y":0x8311, "Z":0xCE1B, 
    }
    dicParam2 = {
        "a":0x79, "b":0x6F, "c":0x2E2, "d":0x2FA, "e":0xE, "f":0xD,
        "g":0xC, "h":0xB, "i":0x63, "j":0x378, "k":0x4D, "l":0x22B,
        "m":0x5A, "n":0x62, "o":0x1D2C, "p":0x8C7F3, "q":0x288, "r":0x21A,
        "s":0x1, "t":0x40, "u":0x4B, "v":0x4E, "w":0x26, "x":0x5,
        "y":0x8, "z":0x1C8, 
        "A":0x1610, "B":0x2, "C":0x270F, "D":0x46FF33C, "E":0x8B3C, "F":0x8618,
        "G":0x6C81C, "H":0x27E945, "I":0x2FC7C3, "J":0xB8F47C, "K":0x115C7, "L":0x12B54,
        "M":0xB348C, "N":0x357CE174, "O":0x317CD7, "P":0x7DD834, "Q":0x39CD0, "R":0xBF44A,
        "S":0x854686, "T":0x13220, "U":0x302E, "V":0x1C43, "W":0x2BA96C08, "X":0x4EFC8,
        "Y":0x1C46, "Z":0xB1664, 
    }

    checkName = helloEnter()    
    param1 = 0
    param2 = 0
    for _char in checkName:
        param1 += dicParam1[_char]
        param2 += dicParam2[_char]

    if(param1 == 0 or param2 == 0):
            print("Can't All Num")
    
    helloEnd(param1)
    helloEnd(param2)

def twentySecondFrom160():
    strCaption = "bPe CrackMe   v1.0                                                                                                                           This CrackMe it's to trainer your VB cracking ability                                                                                                                           Developed by CarLitoZ"
    retVar = strCaption[5:6] + strCaption[8:9] + strCaption[142:143] + \
        strCaption[15:16] + strCaption[160:161] + strCaption[170:171] + \
        strCaption[165:166] + strCaption[167:168] 
    print(retVar)

def twentyThirdFrom160():
    keyCheck = 0xF6EEDB88
    checkName = helloEnter() 

    lenCheckName = len(checkName)
    listCheckName = list(checkName)
    for i in range(0x10):
        xorPara = 0
        for j in range(4):    
            if(0xf-i+3-j < lenCheckName):
                xorPara = (xorPara << 8)
                xorPara += ord(listCheckName[(0xf - i)+(3-j)])
        keyCheck ^= xorPara
        keyCheck -= 1
    print(keyCheck)

def twentyFourthFrom160():
    data = '55 8B EC 83 C4 FC 8B 45 0C 83 F8 10 75 0D 6A 00 E8 6B 02 00 00 33 C0 C9 C2 10 00 83 F8 0F 75 0E \
            8B 45 08 E8 18 01 00 00 33 C0 C9 C2 10 00 83 F8 01 75 06 33 C0 C9 C2 10 00 3D 11 01 00 00 0F 85 \
            E7 00 00 00 8B 45 14 3B 05 60 31 40 00 75 1A 6A 00 68 96 30 40 00 68 A7 30 40 00 FF 75 08 E8 17 \
            02 00 00 33 C0 C9 C2 10 00 3B 05 58 31 40 00 74 0C 3B 05 54 31 40 00 0F 85 AE 00 00 00 C7 05 D9 \
            12 40 00 54 45 58 00 6A 00 8D 45 FC 50 6A 64 FF 35 50 31 40 00 E8 BC 01 00 00 83 7D FC 00 74 5F \
            50 6A 14 68 6C 31 40 00 FF 35 54 31 40 00 E8 AF 01 00 00 85 C0 74 48 A1 0B 30 40 00 BB 6C 31 40 \
            00 03 03 43 81 FB 7C 31 40 00 75 F5 5B 03 C3 31 05 D9 12 40 00 C1 E8 10 66 29 05 D9 12 40 00 BE \
            EC 11 40 00 B9 3E 00 00 00 33 DB EB 04 00 00 00 00 AD 33 D8 49 75 FA 81'
    # xx xx xx xx 为(jmp xx==> eb 26 到 24, 2字节， 如果eb在第二个或者第三个xx，前面的xx必须为90，否则xx随意)
    # 还有 26-24 填充标准为 eb位置，当eb于第一个xx为 26，第二个为25，第三个为24
    # 如： eb 26 xx xx   |   90 eb 25 xx  |    90 90 eb 24
    little_en = data.replace(' ', '').encode('utf-8')
    key = 0
    for i in range(0, 0x3E * 8, 2 * 4):
        temp = big_smaill_end_convert(little_en[i:i+8])
        key = key ^ int(temp, 16) & 0xffffffff

    key = 0xAFFCCFFB ^ key
    result = big_smaill_end_convert((hex(key)[-2:] + hex(key)[2:-2]).encode('utf-8'))

    paramKey = 'CTEX'
    listKey = list(paramKey)
    for i in range(0, len(listKey), 1):
        listKey[i] = ord(listKey[i])
    checkName = helloEnter() 
    listCheckName = list(checkName)
    for i in range(0, len(checkName), 1):
        for j in range(0, 4, 1):
            if (i + j < len(checkName)):
                listKey[j] = (listKey[(j) % 4] + ord(listCheckName[i+j])) & 0xFF

    hexKey = ''
    for v in listKey:
        hexKey = hex(v)[2:] + hexKey

    # 0xeb265458
    # result = 0x00584554 ^ (listKey + pass) - (listKey + pass) >> 16
    # high 16 = 
    defaultCheck = 0x584554
    hexDefaultCheck = hex(defaultCheck)[2:]
    while(len(hexDefaultCheck) < 8):
        hexDefaultCheck = '0' + hexDefaultCheck
    
    lowHexDefaultCheck = int(hexDefaultCheck[-4:], 16)
    highHexDefaultCheck = int(hexDefaultCheck[0:4], 16)

    highHexKey = int(hexKey[:4], 16)
    lowHexKey = int(hexKey[4:], 16)

    strResult = big_smaill_end_convert(result).decode('utf-8')
    highResult = int(strResult[:4], 16)
    lowResult = int(strResult[4:], 16)

    highPass = highResult ^ highHexDefaultCheck 
    lowResult = lowResult + highPass
    lowPass = lowResult ^ lowHexDefaultCheck
    passwordAdd = highPass * 0x10000 + lowPass
    checkCode = (passwordAdd - (highHexKey * 0x10000 + lowHexKey)) & 0xffffffff
    helloEnd(checkCode)

def twentyFifthFrom160():
    helloEnd("55555")

def twentySixthFrom160():
    checkName = helloEnter() 
    lenCheckName = len(checkName)
    if (lenCheckName < 4):
        print("Name must more than 4 character")
        return
    
    ascKey = ord(checkName[0:1])
    
    loopfloat = (432.4 * ascKey * 17.79) / 15
    loopInt = int(loopfloat)
    checkCode = str(loopInt+ascKey) + hex(loopInt - ascKey * 0x19)[2:].upper() + hex(loopInt)[2:].upper() + str(ascKey * lenCheckName -0x1b) + str(lenCheckName) +"-CM"
    helloEnd(checkCode)

def twentySenvenFrom160():
    # GetDriveTypeA (String drive) Library ″kernel32.dll″
    # 参数为一个盘符（如“C:"），
    # 返回值：1表示未知，2表示软驱，3表示本地硬盘，4表示网络驱动器，5表示光驱。因此如下代码可以获得光盘的盘符：
    # 选择一个CD_CHECK.DAT 放于光盘中，即可解开
    pass

def twentyEighthFrom160():
    passwordHex = "363238372D41"
    password = ""
    for i in range(0, len(passwordHex), 2):
        hexSing = passwordHex[i:i+2]
        password += chr(int(hexSing, 16))
    print(password)

def twentyninethFrom160():
    checkName = helloEnter()
    if(len(checkName) < 6):
        print("name must than 5 character")
        return

    nameLooper = 1
    passLooper = 0xA
    checkCode = ""

    for _char in checkName:
        passCode = ord(_char) ^ nameLooper ^ passLooper
        checkCode += chr(passCode)
        nameLooper+=1
        passLooper+=1

    helloEnd(checkCode)

def thirtythFrom160():
    checkName = r"qBQSYdXUe_B\V"
    checkCode = ""
    index = 0
    for _char in checkName:
        if (index % 4 == 0):
            checkCode += chr(ord(_char) ^ ord('2'))
        else:
            checkCode += chr(ord(_char) ^ ord('0'))
        index+=1
    helloEnd(checkCode)

def thirtyFirstFrom160():
    checkName = "VeiajeEjbavwij"
    checkCode = ""
    listCheckName = list(checkName)
    
    for index in range(len(checkName)):
        if (index % 4 == 0):
            checkCode += chr(ord(listCheckName[index]) ^ ord('4') ^ ord('2'))
        else:
            checkCode += chr(ord(listCheckName[index]) ^ ord('4') ^ ord('0'))
    helloEnd(checkCode)


def thirtythSecondFrom160():
    checkName = helloEnter()
    checkCode = ""
    index = 0
    if(len(checkName) < 5):
        print("name must more than 4 character")
        return

    for _char in checkName:
        index+= 1
        if index == 2:
            continue
        if index > 5:
            break
        chec = str(int(ord(_char) / 0xA))
        if len(chec) > 1:
            checkCode += "1"
        else:
            checkCode += chec

    helloEnd(checkCode)

def thirtythThirdthFrom160():
    checkName = helloEnter()
    checkNop = 0
    for _char in checkName:
        if _char >= 'a'and _char <= 'z':
            _char = chr(ord(_char) - 0x20)
        checkNop += ord(_char)
    checkNop = checkNop ^ 0x5678 ^0x1234
    helloEnd(checkNop)

def thirtythFourthFrom160():
    checkName = ""
    while(len(checkName) < 14):
        a_str = string.ascii_letters
        random_letter = random.choice(a_str)
        checkName += random_letter
    
    checkAdd = 0
    index = 0
    for _char in checkName:
        temp = ord(_char) ^ (ord('A') + index)
        if temp == 0:
            break
        checkAdd += temp
        index += 1
        if index == 0xE:
            break
    checkAdd ^= 0x12345678
    checkCode = struct.pack('i', checkAdd)

    #写入文件
    with open('CRACKME3.KEY', 'wb') as wf:
        wf.write(checkName.encode('utf-8'))
        wf.write(checkCode)

def thirtythFifthFrom160():
    helloEnd("..........")

def thirtythSixthFrom160():
    helloEnd("..........")

def thirtythSeventhFrom160():
    # 条件 C3 C2 C0
    # ST(0) > SRC 0 0 0
    # ST(0) < SRC 0 0 1
    # ST(0)  SRC 1 0  0
    # 无序* 1 1 1
    helloEnd("315751288")

def thirtyEighthFrom160():
    checkName = helloEnter()
    checkAscii = ""
    for _char in checkName:
        checkAscii += str(ord(_char))
    
    checkAscii = int(checkAscii)
    while checkAscii > 999999999:
        checkAscii = int(checkAscii / 3.141592654)
    checkAscii ^= 0x30F85678
    checkAscii -= 55475

    checkCode = checkAscii + len(checkName)
    print(checkCode)

def thirtyNinethFrom160():
    checkName = helloEnter()
    nIndex = 0

    nAddStr = 0
    keyBenefit = 0x44414d4e
    for _char in checkName: #firstLoop
        nAddStr += ord(_char) 
        keyBenefit = circular_shift_right(keyBenefit, 1 + nIndex, 32)
        nIndex += 1
        keyBenefit ^= nAddStr
    keyBenefit |= 0x10101010

    checkCode = ""
    for _ in range(8):
        keyBenefit = circular_shift_left(keyBenefit, 4, 32)
        ckeckByte = keyBenefit & 0xf
        checkCode += str(hex(ckeckByte)[2:])
    helloEnd(checkCode)

def fortythFrom160():
    checkName = helloEnter()
    checkCode = ""

    for _char in checkName:
        checkCode += chr(ord(_char) + 5)
    
    helloEnd(checkCode)

def fortythFirstFrom160():
    # 41.cpp
    pass

def fortythSecondFrom160():
    # 42.cpp
    pass

def fortythForthFrom160():
    listEnterkey = [0x18, 0x25, 0x42, 0x0c, 0x0d, 0x06,
                    0x36, 0x2b, 0x17, 0x2f, 0x13, 0x82,
                    0x9b, 0x92, 0x03, 0x63, 0x21, 0x42,
                    0x5c, 0x29, 0xc7, 0x66, 0x58, 0x0a,
                    0x28, 0x50]
    checkName = helloEnter()
    nameAdd = 0
    newName = "_" + checkName.lower()
    nameMul = len(checkName)

    if (nameMul < 6):
        print("waring: name must has more than 6 num")
        return

    index = 0
    for _char in newName:
        index += 1
        if index > 6:
            break
        intChar = ord(_char) - 0x61
        if (intChar <= 0x19 and intChar >= 0):
            nameAdd += listEnterkey[intChar]
        else:
            nameAdd += 0x5d
        nameAdd &= 0xff
    nameMul *= 0x4a7e
    checkCode = str(nameAdd) + "-" + str(nameMul)
    helloEnd(checkCode)

def fortythFifthFrom160():
    checkName = helloEnter()
    nameAdd = 0x37
    for _char in checkName:
        nameAdd += ord(_char) << 9
    helloEnd(nameAdd)

def fortythSixthFrom160():
    # see 46dll.cpp
    pass

def fortythSeventhFrom160():
    tempEsi = 0
    listOut = []

    checkName = helloEnter()
    if(len(checkName) > 0xf):
        print("name not than 13 code")
        return

    with open("tasks41~50\due-cm2.dat","wb") as fout:
        # loop1 for esi == 
        while tempEsi < 0x1d5:
            numCode = random.randint(0,9) + 0x30
            if tempEsi + numCode > 0x1d5:
                numCode = 0x1d5 - tempEsi
            listOut.append(numCode)
            s = struct.pack('B',numCode)
            fout.write(s)
            tempEsi += numCode
        s = struct.pack('B',0x01)
        fout.write(s)
        listOut.append(0x01)

        # loop1 for name == 
        nIndex = 0
        for _char in checkname:
            xor_char = ord(_char) ^ listOut[nIndex]
            s = struct.pack('B',xor_char)
            fout.write(s)
            listOut.append(xor_char)
            nIndex += 1
        s = struct.pack('B',0x01)
        fout.write(s)
        listOut.append(0x01)

        # loop1 for esi == 
        tempEsi = 0
        while tempEsi < 0x1b2:
            numCode = random.randint(0,9) + 0x30
            if tempEsi + numCode > 0x1b2:
                numCode = 0x1b2 - tempEsi
            listOut.append(numCode)
            s = struct.pack('B',numCode)
            fout.write(s)
            tempEsi += numCode

def findNumsEqualValue(listNums, begin, target, listTemp, listExpict):
    listInsTemp = listTemp[:]
    if target == 0:
        listExpict.append(listInsTemp)
        return
    if target < 0:
        return

    for i in range(len(listNums)):
        if i < begin:
            continue
        
        listInsTemp.append(i)
        findNumsEqualValue(listNums, i + 1, target - listNums[i], listInsTemp, listExpict)
        listInsTemp.pop()
    

def fortythEighthFrom160():
    # [10,1, 2, 0, 7, 5, 6, 9, a, 
    #  3, b, c, d, e, f,11,4, 8]
    listCheckToIn = [ 0x10, 0x01, 0x02, 0x00, 0x07, 0x05, 0x06, 0x09, 0x0a,
                      0x03, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x11, 0x04, 0x08 ]
    
    listCheckToIn = [ 0x03, 0x01, 0x02, 0x09, 0x10, 0x05, 0x06, 0x04, 0x11,
                      0x07, 0x08, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x00, 0x0f ]
    listButtonNum = [ 0x16, 0x49, 0x5e, 0x15, 0x27, 0x26, 0x21, 0x25, 0x1D,        # 9
                      0x59, 0x53, 0x37, 0x31, 0x48, 0x5D, 0x0C, 0x61, 0x52, 0x4D ]
    
    listCheckedNum = []
    checkNum = int(0xF35466 / 0x4D) 

    for i in range(len(listButtonNum) - 1):
        listCheckedNum.append(listButtonNum[i] * listButtonNum[i + 1] * (i + 1))
    print(listCheckedNum)

    listExipre = []
    findNumsEqualValue(listCheckedNum, 0, checkNum, [], listExipre)
    print(listExipre)
    checkCode = []
    if len(listExipre) < 0:
        print("error")
        return
    else:
        for listExp in listExipre:
            codeSin = []
            dd = 0
            for index in listExp:
                codeSin.append(listCheckToIn[index])
                codeSin.sort()
            print(dd)
            checkCode.append(codeSin)
    print(checkCode)

def fortythNinethFrom160():
    nameCheck = '1LSK2DJF4HGP3QWO5EIR6UTYZ8MXN7CBV9'
    listNameCheck = [0x41]
    listPassCheck = [0x53]
    for _char in nameCheck:
        listNameCheck.append(ord(_char))
    passCheck = 'U7CSJKF09NCSDO9SDF09SDRLVK7809S4NF'
    for _char in passCheck:
        listPassCheck.append(ord(_char))

    checkName = helloEnter()
    if(len(checkName) > 8):
        print("ERROR")
        return
    
    checkCode = ""
    for _char in checkName:
        ord_char = ord(_char)
        if _char > 'Z':
            ord_char = ord(_char) - 0x20
        i = 0
        for i in range(len(listNameCheck)):
            if ord_char == listNameCheck[i]:
                checkCode += chr(listPassCheck[i])
                break
    helloEnd(checkCode)

def fiftythFrom160():
    # 50dll.cpp
    pass

def fiftyFirstFrom160():
    blockCheckPre = 0x36455544
    blockCodePre = 0x4071885
    blockCheckAfter = 0x43534952
    blockCodeAfter = 0x4b00d127

    rolPre = 0
    rolAfter = 0
    while (blockCheckPre != blockCodePre):
        rolPre += 1
        al = blockCodePre & 0xff
        blockCodePre -= al
        al = al - rolPre & 0xff
        blockCodePre += al

        ah = blockCodePre & 0xff00
        ah = int(ah / 0x100)
        blockCodePre -= ah * 0x100
        ah = ah ^ al
        blockCodePre += ah * 0x100
        blockCodePre & 0xffffffff

        blockCodePre = circular_shift_right(blockCodePre, 6, 32)
        # blockCheckPre = circular_shift_left(blockCheckPre, 6, 32)
        # ah = blockCheckPre * 0xff00 / 0xff
        # al = blockCheckPre * 0xff
        # ah = ah ^ al *0xff
        # blockCheckPre = blockCheckPre - blockCheckPre * 0xff00 + ah
        

    # while (blockCheckAfter != blockCodeAfter):
    #     blockCheckAfter = circular_shift_left(blockCheckAfter, 6, 32)
    #     ah = blockCheckAfter * 0xff00 / 0xff
    #     al = blockCheckAfter * 0xff
    #     ah = ah ^ al *0xff
    #     blockCheckAfter = blockCheckAfter - blockCheckAfter * 0xff00 + ah
    #     rolAfter += 1

    print(rolPre)
    #see 51.cpp

def fiftySecondFrom160():
    # see 52.cpp
    pass

def fiftyThirdFrom160():
    # see 53.cpp but not dewcrypt
    pass

def fiftyFourthFrom160():
    listNameVar = list("LANNYDIBANDINGINANAKEKHYANGNGENT")
    listCodeVar = list("LANNY5646521")

    nInterCode = 0
    checkName = helloEnter()
    checkCode = ""
    listCheckName = list(checkName)

    for index in range(len(checkName)):
        nInterCode += ord(listCheckName[index])
        nInterCode = nInterCode << 8
        nInterCode &= 0xffffffff
        nInterCode += ord(listNameVar[index])
        
        if(nInterCode & 0x80000000):
            nInterCode ^= 0xffffffff
            nInterCode += 1
    nInterCode ^= 0x12345678

    lenInterCode = len(list(str(nInterCode)))
    
    for index in range(lenInterCode):
        checkCode += listCodeVar[nInterCode % 0xA]
        nInterCode = int(nInterCode / 0xA)

    helloEnd(checkCode)

def fiftyFifthFrom160():
    # see 55.cpp but unknow mean,maybe just change dialog function
    pass

def fiftySixFrom160():
    # unknow mean
    pass

def fiftySeventhFrom160():
    nButton = random.randint(1,8)
    nButton = 8
    # String
    if nButton == 1:
        print("Button: " + "String")
        print("Key:    " + "String")
    # Variant
    elif nButton == 2:
        print("Button: " + "Variant")
        print("Key:    " + "Empty")
    # Long
    elif nButton == 3:
        print("Button: " + "Long")
        print("Key:    " + str(0x2C2FAE))
    # Currency
    elif nButton == 4:
        print("Button: " + "Currency")
        print("Key:    " + str(0x8180754 / 10000))
    # Single
    elif nButton == 5:
        print("Button: " + "Single")
        print("Key:    " + str(9764317691904))
    # Double
    elif nButton == 6:
        print("Button: " + "Double")
        print("Key:    " + str(147258369789456000))
    # Integer
    elif nButton == 7:
        print("Button: " + "Integer")
        print("Key:    " + str(0x5BEF))
    # Byte
    elif nButton == 8:
        print("Button: " + "Byte")
        print("Key:    " + str(0xEF))

def fiftyEighthFrom160():
    print("Key:    " + "use hexeditor to look for hardcoded codes")

def fiftyNinthFrom160():
    CheckNum = [
        84, 104, 105, 115, 32, 105, 115, 32, 116, 104, 101, 32, 
        99, 111, 114, 114, 101, 99, 116, 32, 99, 111, 100, 101,
    ]
    CheckCode = ""
    for i in CheckNum:
        CheckCode += chr(i)
    print("Key:    " + CheckCode)

def SixtythFrom160():
    CheckNum = [
        0x52, 0x65, 0x76, 0x65, 0x72, 0x73, 0x65  
    ]

    CheckCode = ""
    for i in CheckNum:
        CheckCode += chr(i)
    print("Key:    " + CheckCode)

def SixtyFirstFrom160():
    mYear = datetime.date.today().year
    mYear %= 100
    mMonth = datetime.date.today().month
    mDay = datetime.date.today().day
    mMonth = 5
    mDay = 21

    CheckCode = str(mYear) + " " + str((mYear + mMonth)*mMonth) + " " + str(((mYear + mMonth)*mMonth + mDay) * mDay)
    print("Key:    " + CheckCode)

def SixtySecondFrom160():
    checkName = helloEnter()
    listCheckName = list(checkName)
    checkCode = ""

    for i in range(len(checkName)):
        if i % 2 == 0:
            strCheckNum = str(ord(listCheckName[i]))
            nTemp = 0
            for _single in strCheckNum:
                nTemp += int(_single)
            checkCode +=  str(nTemp)
        else:
            checkCode += listCheckName[i]
    helloEnd(checkCode)
    
def SixtyThirdFrom160():
    CheckCode = "Correct...Error"
    print("Key:    " + CheckCode)

def SixtyfourthFrom160():
    checkName = helloEnter()

    nTotal = 0
    checkUpper = checkName.upper()
    for _char in checkUpper:
        nTotal += (ord(_char) - 0x40) * 0x82
        nTotal += 0x50 << 4
    
    checkCode = str(nTotal)
    helloEnd(nTotal)

def SixtyFifthFrom160():
    checkName = helloEnter()
    if (len(checkName) < 5):
        print("error less than 5")
        return 

    checkCode = ""
    index = 0
    for _char in checkName:
        checkCode += chr(ord(_char) - index)
        index+=1
    helloEnd(checkCode)
    
def SixtySixthFrom160():
    checkName = helloEnter()
    lenCheckName = len(checkName)
    listCheckName = list(checkName)
    checkStr = ""

    for index in range(10):
        if(index + 10 < lenCheckName):
            checkStr += chr((ord(listCheckName[index + 10]) ^ ord(listCheckName[index])) % 10 + 0x30)
        else:
            if(index < lenCheckName):
                checkStr += chr((0x20 ^ ord(listCheckName[index])) % 10 + 0x30)
            else:
                checkStr += chr((0x20 ^ 0x20) % 10 + 0x30)
    checkStr += '6'
    helloEnd(int(checkStr))

def SixtySeventhFrom160():
    checkName = helloEnter()
    lenCheckName = len(checkName)
    listCheckName = list(checkName)
    checkCode = ""

    for index in range(lenCheckName):
        codeChar = ord(listCheckName[index]) ^ index
        codeChar += (lenCheckName) ^ index
        if codeChar < 0x20:
            codeChar += 0x20
        elif codeChar > 0x80:
            codeChar = 0x20
        checkCode += chr(codeChar)
    checkCode = checkCode[::-1]
    helloEnd(checkCode)

def SixtyEighthFrom160():
    bVerify = "203945709398475029384750293875577934765620110289347563929867122287863095762304984875020398746563"
    listVerify = list(bVerify)
    checkName = helloEnter()
    checoCode = ""

    for _char in checkName:
        checoCode += listVerify[ord(_char) - 0x20]

    helloEnd(checoCode)

def SixtyNinthFrom160():
    SixtyEighthFrom160()

def SeventythFrom160():
    checkName = helloEnter()
    listCheckName = list(checkName)
    checkCode = ""

    for i in range(8):
        codeIndex = (ord(listCheckName[i]) ^ ord(listCheckName[7 - i])) % 8
        codeChar = listCheckName[codeIndex]
        checkCode += codeChar
    helloEnd(checkCode)

def SeventyFirstFrom160():
    checkName = helloEnter()
    checkCode = checkName + checkName + "625g72"
    print(checkCode)

def SeventySecondFrom160():
    CheckCode = "RIDERSINTHENIGHT"
    print("Key:    " + CheckCode)

def SeventyThirdFrom160():
    checkName = helloEnter()
    codeNum = 0x2b67
    for _char in checkName:
        codeNum += 0x2b67
        codeNum += ord(_char)
    helloEnd(codeNum)

def SeventyFourthFrom160():
    CheckCode = "Regcode"
    print("Key:    " + CheckCode)

def SeventyFifthFrom160():
    ebx = 0x49390305
    esi = 0x48631220
    checkName = "1234" #helloEnter()
    checkCode = ""

    for _char in checkName:
        ordNum = ord(_char)
        ebx ^= ordNum
        esi ^= ebx
        lastNum = ebx & 1
        if ebx % 2 == 1:
            ebx = shift_arithmetic_right(ebx, 1) 
            if ebx & 0x8fffffff:
                ebx += lastNum
            ebx ^= 0x1200311
        else:
            ebx = shift_arithmetic_right(ebx, 1) 
            if ebx & 0x8fffffff:
                ebx += lastNum
    checkCode = hex(ebx & 0xffff)[2:] + "-" + hex(ebx >> 0x10)[2:] + "-" + hex(esi & 0xffff)[2:] + "-" + hex(esi >> 0x10)[2:]
    checkCode = checkCode.upper()
    print(checkCode)

def SeventySixthFrom160():
    # 第一部分
    print("First Serial Case:")
    listCode = [0x54, 0x65, 0x48, 0x6E, 0x45, 0x64]
    checkCode = ""
    for code in listCode:
        checkCode += chr(code)
    print("Key:    " + checkCode)

    # 第二部分
    print("Second N/P Case:")
    checkName = "1234" #helloEnter()
    ebx = 0x94390304
    esi = 0x84631221
    checkCode = ""

    for _char in checkName:
        ordNum = ord(_char)
        ebx ^= ordNum
        esi ^= ebx
        lastNum = ebx & 1
        
        if ebx % 2 == 1:
            ebx = shift_arithmetic_right(ebx, 1) 
            if ebx & 0x8fffffff:
                ebx += lastNum
            ebx ^= 0x1200311
        else:
            ebx = shift_arithmetic_right(ebx, 1) 
            if ebx & 0x8fffffff:
                ebx += lastNum

    checkCode = hex(ebx & 0xffff)[2:] + "-" + hex(ebx >> 0x10)[2:] + "-" + hex(esi & 0xffff)[2:] + "-" + hex(esi >> 0x10)[2:]
    checkCode = checkCode.upper()
    print("Name:      " + checkName)
    print("Serial:    " + checkCode)

    # 第三部分
    print("Third File Case:")
    print("see task file 76.dat")

def SeventySeventhFrom160():
    mCode = 582935
    checkCode = int(mCode / 0x78c)
    checkCode *= 0x399
    checkCode = checkCode << 0x11
    checkCode &= 0xffffffff
    checkCode = checkCode >> 9
    checkCode = int(checkCode / 0xC)
    print(checkCode)

def SeventyNinthFrom160():
    checkCode = "VL - -3585902..46119.-208490."
    print("Key:    " + checkCode)

def EightythFrom160():
    checkName = input("Please Enter Your Name!\n")
    checkCompany = input("Please Enter Your Company!\n")
    nCheckNum = int(0x7B / (len(checkName) + len(checkCompany)))
    nCheckNum = nCheckNum << 5
    nCheckNum -= 0x2c115c
    nCheckNum += 0x872eb0
    nCheckNum ^= 0x12
    print("Key:    " + nCheckNum)

def EightyFirstFrom160():
    rsaE = 9901
    rsaN = 12790891
    listKey = [8483678, 5666933]
    checkCode = ""
    
    for suNum1 in range(int(math.sqrt(rsaN)) + 1):
        if suNum1 == 1 or suNum1 == 0:
            continue

        if(rsaN % suNum1 == 0):
            break
    fn = (suNum1 -1) * (rsaN/suNum1 - 1)
    d = int(extend_Gcd(rsaE, fn))
    for key in listKey:
        m = fast_power_with_mod(key, d, rsaN)
        checkCode += str(m)
    print("Key:    " + checkCode)

def EightySecondFrom160():
    listArg = [ # 40300B  # ebx                   # edx
                    0x10, 0xE0, 0x00, 0x00, 0x00, 0xF0, 0x03, 0x00, 0x00, # GetTextToEbx name
        0x0B, 0x00, 0x10, 0xF5, 0x00, 0x00, 0x00, 0xF1, 0x03, 0x00, 0x00, # GetText serial
        0x16, 0x00, 0x08, 0xDC, 0x00, 0x00, 0x00, 0xDC, 0x00, 0x00, 0x00, # ebx - edx (base+)   # (dc) = 0
        0x21, 0x00, 0x04, 0xDC, 0x00, 0x00, 0x00, 0x5A, 0x01, 0x00, 0x00, # ebx + edx (base+)   # (dc) += (5A)
        0x2C, 0x00, 0x20, 0xE0, 0x00, 0x00, 0x00, 0x4E, 0x01, 0x00, 0x00, # StoEbxToloalAndEbx(DWORD) # TO(E0) ()edx is index   <----
        0x37, 0x00, 0x04, 0x4E, 0x01, 0x00, 0x00, 0x56, 0x01, 0x00, 0x00, # ebx + edx (base+)   # (14e) += (156) ebx -=1               |
        0x42, 0x00, 0x04, 0x4A, 0x01, 0x00, 0x00, 0xDC, 0x00, 0x00, 0x00, # ebx + edx (base+)   # (14A) += (DC) #testname           |
        0x4D, 0x00, 0x08, 0x52, 0x01, 0x00, 0x00, 0x56, 0x01, 0x00, 0x00, # (152) -= (156)  for(0->20)(20 - 1)                      |
        0x58, 0x00, 0x18, 0x52 ,0x01, 0x00, 0x00, 0x00, 0x00, 0x2C, 0x00, # checkForEbx     (152 is zero?)--------------------------|
        0x63, 0x00, 0x20, 0x66, 0x01, 0x00, 0x00, 0x52, 0x01, 0x00, 0x00, # MoveLocal                       <------------------------
        0x6E, 0x00, 0x0C, 0x4A, 0x01, 0x00, 0x00, 0xDC, 0x00, 0x00, 0x00, # XOr LastCode ^ D4E1C094 -> (4A)                         |
        0x79, 0x00, 0x04, 0x52, 0x01, 0x00, 0x00, 0x62, 0x01, 0x00, 0x00, # (52) += 4                                                |
        0x84, 0x00, 0x08, 0x4E, 0x01, 0x00, 0x00, 0x62, 0x01, 0x00, 0x00, # 0x14 - 4                                                |
        0x8F, 0x00, 0x18, 0x4E, 0x01, 0x00, 0x00, 0x00, 0x00, 0x63, 0x00, # checkForEbx 5() loop------------------------------------|
        0x9A, 0x00, 0x24, 0x7A, 0x01, 0x00, 0x00, 0xF1, 0x03, 0x00, 0x00, # GetInt 7D4B749F  ->ebx
        0xA5, 0x00, 0x08, 0x4A, 0x01, 0x00, 0x00, 0x7A, 0x01, 0x00, 0x00, # ebx - int
        0xB0, 0x00, 0x18, 0x4A, 0x01, 0x00, 0x00, 0x00, 0x00, 0xC6, 0x00, # cmp ebx ->
        0xBB, 0x00, 0x14, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, # MessageBox Correct
        0xD1, 0x00, 0x14, 0x0A, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, # MessageBox InCorrect
        0xD1, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 
    ]

    listXorArg = [
        0xd4e1c094, 0xff1f9811, 0x91fabbc8, 0x781d9410, 0x918ffabc
    ]
    argXORInfo = 0
    for arg in listXorArg:
        argXORInfo ^= arg

    checkName = helloEnter()
    lenCheckName = len(checkName)
    listCheckName = list(checkName)
    for _add in range(20 - lenCheckName):
        listCheckName += [chr(0)]

    hexInfo = 0
    valueThird = 0
    valueFouth = 0

    for index in range(19):
        if index < 17:
            temp = ord(listCheckName[index+3]) << 0x18 | ord(listCheckName[index+2]) << 0x10 | ord(listCheckName[index+1]) << 0x8 | ord(listCheckName[index])
            hexInfo = (temp + hexInfo) & 0xffffffff

        elif index == 17:
            temp = ord(listCheckName[index+2]) << 0x10 | ord(listCheckName[index+1]) << 0x8 | ord(listCheckName[index])
            hexInfo = (temp + hexInfo) & 0xffffffff

        else:
            for valueThird in range(10):
                hexCheckThird = hexInfo
                temp = (valueThird + 0x30) << 0x18 | ord(listCheckName[index+1]) << 0x8 | ord(listCheckName[index])
                hexCheckThird = (temp + hexCheckThird) & 0xffffffff

                for valueFouth in range(10):
                    hexCheckFourth = hexCheckThird
                    temp = (valueFouth + 0x30) << 0x18 | (valueThird + 0x30) << 0x10 | ord(listCheckName[index+1])
                    hexCheckFourth = (temp + hexCheckFourth) & 0xffffffff

                    hexCheck = hexCheckFourth ^ argXORInfo
                    temp = hexCheck
                    while temp >= 100:
                        temp = int(temp / 10)
                    if int(temp / 10) == valueThird and int(temp % 10) == valueFouth:
                        helloEnd(hexCheck)
                        return

def EightyThirdFrom160():
    checkName = "12345" # helloEnter()
    checkCode = ""
    
    for _char in checkName:
        checkCode += str(ord(_char))
    checkCode = checkCode[1:]
    helloEnd(checkCode)

def EightyFourthFrom160():
    nButton = random.randint(1,8)
    # Easy Serial
    if nButton == 1:
        print("Button: " + "Easy Serial")
        print("Key:    " + "23784628356267")
    # Harder Serial
    elif nButton == 2:
        print("Button: " + "Harder Serial")
        print("Key:    " + "ADUJSDMD8387079498SOPEMNSD")
    # Name/Serial
    elif nButton == 3:
        checkName = helloEnter()
        checkCode = ord(checkName[-1:]) * 13 + 161
        checkCode = checkCode * checkCode * 154
        
        print("Button: " + "Name/Serial")
        print("Key:    " + checkCode)

    # Matrix
    elif nButton == 4:
        print("Button: " + "Matrix")
        print("Key:    " + "1, 6, 7, 10, 20, 23")

    # KeyFile
    elif nButton == 5:
        print("Button: " + "KeyFile")
        print("FileName:" + "wk.dat")
        print("Key:     " + "Easy, eh?")

    # NAG
    elif nButton == 6:
        print("Button: " + "NAG")
        print("Key:    " + "0x416A60, 0x40FCD0 set retn")

    # Cripple
    elif nButton == 7:
        print("Button: " + "Cripple")
        print("Key:    " + "Set resource")

def EightyFifthFrom160():
    checkName = helloEnter()
    checkCode = ord(checkName[:1]) + 0x28193F53 - 0x224
    helloEnd(checkCode)

def EightySixthFrom160():
    pass

def EightySeventhFrom160():
    checkName = input("Please Enter Your Name!\n")
    checkCompany = input("Please Enter Your Company!\n")
    checkcode = str(len(checkCompany) * len(checkName) + 999081)
    checkcode = checkcode + ":-)"
    print(checkcode)

def NintythFrom160():
    checkXor = [
        0x75, 0x3f, 0x8b, 0x41, 0xd2, 0xff, 0xb1, 0x18, 0xdb, 0x49, 0xb8, 0x52
    ]
    checkString = [
        0x20, 0x76, 0xc8, 0x1e, 0xb4, 0x90, 0xc3, 0x7d, 0xad, 0x2c, 0xca, 0x72
    ]

    index = 0
    checkCode = ""
    for mbyte in checkString:
        checkCode += chr(mbyte ^ checkXor[index])
        index += 1
    helloEnd(checkCode)

    # register
    checkRegisterKeyXor = [
        0x65, 0x4a, 0xb5, 0x89, 0x12, 0x58, 0x9f, 0xff, 0xfb, 0xed, 0x55, 0x21,
        0xa8, 0x7b, 0xce, 0xe5, 0x18, 0x97, 0x45, 0x3a, 0x12, 0x37, 0x77, 0xee, 0x58
    ]
    checkRegisterKeyString = [
        0x3f, 0x3f, 0xd7, 0xed, 0x67, 0x34, 0xf3, 0x9e, 0x97, 0x81, 0x34, 0x0f, 
        0x86, 0x55, 0xac, 0x9c, 0x38, 0xc6, 0x30, 0x5f, 0x63, 0x42, 0x12, 0x9c, 0x37
    ]
    index = 0
    checkKeyCode = ""
    for mbyte in checkRegisterKeyString:
        checkKeyCode += chr(mbyte ^ checkRegisterKeyXor[index])
        index += 1
    
    checkRegisterExeXor = [
        0x6f, 0x45, 0x4b, 0x8c, 0x9a, 0x21, 0x18, 0x46, 0x1a, 0x69, 0x97, 0x4a,
        0x5f, 0x2d, 0x3c, 0x8a, 0x9b, 0x54, 0x6d, 0x12
    ]
    checkRegisterExeString = [
        0x28, 0x2a, 0x24, 0xe8, 0xba, 0x6d, 0x6d, 0x25, 0x71, 0x49, 0xd4, 0x38, 
        0x3e, 0x4e, 0x57, 0xef, 0xe9, 0x75, 0x4c, 0x33
    ]
    index = 0
    checkExeCode = "0" * 176
    for mbyte in checkRegisterExeString:
        checkExeCode += chr(mbyte ^ checkRegisterExeXor[index])
        index += 1
    
    print("Register mask.key:     " + checkKeyCode)
    print("Register mask.exe:     " + checkExeCode)

def CodeNum(cNum):
    nNum = 0
    CheckNum = cNum
    while CheckNum >0:
        nNum += 1
        CheckNum /= 0x100
    return nNum

def checkCode(a, b, c):
    print(a, b, c)
    edi = 0
    esi = 0
    nLen = 0
    if c != 0:
        nLen = CodeNum(c) + 8
    elif b != 0:
        nLen = CodeNum(b) + 4
    else:
        nLen = CodeNum(a)
    
    if nLen == 0:
        return False

    EdiCheck = int((a + 0x12ab20 + c) * nLen) ^ (b + 0x48ff4ea) ^ (c - 0xbc309a - a)
    EdiCheck |= 0x29359e2
    EsiCheck = int((a - 0x127fb9 - c) / nLen) ^ (b - 0x48ff4ea) ^ (c + 0xbc0533 + a)
    EsiCheck &= 0x29359e2

    for _ in range(0xff):
        for _ in range(0xff):
            edi += EdiCheck
            edi &= 0x15263748
            esi += EsiCheck
            esi |= 0x596a7b8c
        edi += 0x911
        esi -= 0x911
    
    if edi == 0x20021c51 and esi == 0x5b6b72dd:
        print(a, b, c)
        return True
    return False

def loopCheck(nlen, a, b, c):

    if nlen == 0:
        if(checkCode(a, b, c)):
            return True
    #check
    elif nlen > 8:
        for i in range(0x80):
            loopCheck(nlen - 1, a, b, c * 0x100 + i)
    elif nlen > 4:
        for i in range(0x80):
            loopCheck(nlen - 1, a, b * 0x100 + i, c)
    else:
        for i in range(0x80):
            loopCheck(nlen - 1, a * 0x100 + i, b, c)



def NintyFirstFrom160():
    # last  edi = 0x20021c51
    #       esi = 0x5b6b72dd
    listInput = list("75642456")
    listCheckLoop = []

    # 12 位 最长
    # a 为 0-4 b 5- 8 c 9 - 12
    aIni = 0
    bIni = 0
    cIni = 0
    loopCheck(12, 0, 0, 0)
        
    print(listInput)
    print(listCheckLoop)

def NintyThirdFrom160():
    listFirstJusi = [0x17, 0x2A, 0x13, 0x08, 0x24, 0x76]
    listSecondJust = [
        0x02, 0x27, 0x06, 0x01, 0x3a, 0x1b, 0x0e, 0x25, 0x18, 0x05, 0x31, 0x13,
        0x08, 0x3e, 0x02, 0x20, 0x38, 0x05, 0x17, 0x20, 0x17, 0x0c, 0x21, 0x11,
        0x16, 0x2c
        ]
    listInitCode = ['C', 'i', 'A']
    strSerial = ""
    strMiddleCheck = ""
    for i in range(len(listFirstJusi)):
        strSerial += chr(listFirstJusi[i] ^ ord(listInitCode[i%3]))
    strSerial += chr(0x2d)

    checkName = "12345678" #input("Please Enter Your Name!\n")
    if len(checkName) < 8:
        return
    listCheckName = list(checkName)
    CheckCode = 1
    nIndex = 0
    nPreF = 0
    for c in listCheckName:
        if nIndex < 4:
            if ord(c) & 1:
                nPreF += int(numpy.power(2, 3-nIndex))
        else:
            CheckCode *= (ord(listCheckName[nIndex]) + nPreF)
        nIndex += 1
    
    
    for i in range(len(listSecondJust)):
        strMiddleCheck += chr(listSecondJust[i] ^ ord(listInitCode[i%3]))

    listCheckCode = list(str(CheckCode))
    nIndex = 0
    for c in listCheckCode:
        checkc = int(c)
        checkIndex = checkc + nIndex
        strSerial += strMiddleCheck[checkIndex]
        nIndex += 1

    helloEnd(strSerial)

    nFir = random.randint(10,99)
    nSec = nFir - 9
    nThi = 0x63 - nSec
    nFou = 0x42 - nThi
    edtCode = str(nFir) + chr(0x70) + chr(0x76) + str(nSec) + \
                chr(0x4c) + chr(0x47) + str(nThi) + chr(0x74) + chr(0x58) + str(nFou)
                
    print("only Code is : " + edtCode)

def NintySeventhFrom160():
    checkName = input("Please Enter Your Name!\n")
    if len(checkName) < 6:
        return

    listCheckName = list(checkName)
    lenCheckName = len(checkName)
    checkTotal = 0
    nIndex = 0
    for i in range(6):
        checkTotal += ord(listCheckName[i])

    checkTotal += lenCheckName
    checkTotal *= 0x15c10e
    checkTotal = int(checkTotal / 3)
    checkTotal += 0x29a
    checkTotal = int(checkTotal / 0x1388)
    checkTotal *= lenCheckName
    checkTotal = checkTotal * ord(listCheckName[2]) * ord(listCheckName[4])
    while(checkTotal <= 0x5f5e0ff or checkTotal >= 0x3b9aca00):
        checkTotal += lenCheckName
        checkTotal = (checkTotal * ord(listCheckName[0])) & 0xffffffff 
        if checkTotal & 0x80000000 > 0:
            checkTotal = (checkTotal ^ 0xffffffff) + 1
    helloEnd(checkTotal)

    # deal esi
    while(checkTotal <= 0x2710 or checkTotal >= 0x186a0):
        if checkTotal >= 0x186a0:
            checkTotal = int(checkTotal / lenCheckName)
        if checkTotal <= 0x2710:
            checkTotal *= checkTotal
    print("scroll: " + str(checkTotal))

def NintyEighthFrom160():
    # 1、delete annoy.txt
    # form2 first passWord 123-456-789-000
    # second 456-678
    pass

def HundredthFrom160():
    # add esp, 0x10
    pass

def HUndredFirstFrom160():
    pass

def HundredSixstFrom160():
    checkName = input("Please Enter Your Name!\n")
    if len(checkName) < 4:
        return
    checkCode = checkName[::-1]
    helloEnd(checkCode)

def HundredEightFrom160():
    print("Code: 12011982")

def HundredNinthFrom160():
    print("name: Registered User")
    print("code: GFX-754-IER-954")

def HundredTenthFrom160():
    checkname = helloEnter()
    if len(checkname) < 6:
        return

    checkCode = 0
    for c in checkname:
        checkCode = checkCode + 2 * ord(c)
    checkCode = checkCode + 2 * len(checkname)
    helloEnd(checkCode)

def HundredEleventhFrom160():
    mostlow = 1
    secondlow = 1
    mostIndex = 0
    secondIndex = 0

    for i in range(0x100000000):
        if i == 0:
            continue
        nearpi = i / math.pi
        nearpi = nearpi % 1
        if nearpi > 0.0001:
            continue

        cakc = math.fabs(math.sin(i))
        if (cakc < mostlow):
            secondlow = mostlow
            secondIndex = mostIndex
            mostlow = cakc
            mostIndex = i
        elif (cakc < secondlow):
            secondlow = cakc
            secondIndex = i
        print(i)
        print(mostlow, mostIndex)
        print(secondlow,secondIndex)

    print("first:  411557987")
    print("second: 245850922")

def HundredTwelvethFrom160():
    mySerial = "N54-FF43C24F-05S"
    checkName = "12345678"#helloEnter()
    checkCompany = "87654321"
    checkSeiral = mySerial.replace("-", "")
    nSerial = 0
    nName = 0
    nCompany = 0

    for c in checkSeiral:
        nSerial += ord(c)

    for c in checkName:
        nName += ord(c)

    for c in checkCompany:
        nCompany += ord(c)

    checkCode = "34" + mySerial[4:7] + "-" + str(nSerial) + str(nName)[::-1] + "-" + checkCompany[4:7] + str(nCompany) + "-" + checkName[3:5]
    helloEnd(checkCode)

def HundredThirteenthFrom160():
    print("password: ULTRADMA............................................................")

def HundredTwentySecondFrom160():
    nSerialInfo = 0xF42C34FF
    nSerialxCode = 0
    if nSerialInfo & 0x80000000 > 0:
        nSerialxCode = (nSerialInfo ^ 0xffffffff) + 1
    else:
        nSerialxCode = nSerialInfo
    
    nInputxCode = 989
    
    nInputxCode = ((nInputxCode * 2 + 0x10) * 18) ^ 0x5
    nSerialxCode = int(((nSerialxCode << 2)) / 3)
    nSerialxCode = (nSerialxCode ^ 3) + 0x40

    nInputxCode = (shift_arithmetic_right(nInputxCode * 6, 1) + 0xd) * 0x36
    nInputxCode = (nInputxCode + circular_shift_left(nInputxCode, 5)) ^ 0x10
    nSerialxCode = int(((nSerialxCode * 6)) / 5) ^ 0x25 ^ 0x27

    nInputxCode = ((nInputxCode * 2 + 0xd) * 6 * 0x59) ^ 0x9 
    nSerialxCode = ((nSerialxCode * 5) ^ 0x22) + 0x3

    nInputxCode = ((shift_arithmetic_right(nInputxCode, 1) + 0x10) * 3)  ^ 0x6
    nSerialxCode = (int(((nSerialxCode * 0x2b)) / 3) ^ 0x3) + 0x22

    nInputxCode = (((shift_arithmetic_right(nInputxCode, 1) + 1) * 6) << 3) ^ 6
    nSerialxCode = (shift_arithmetic_right(nSerialxCode * 3, 2) ^ 0x22) + 0x4

    nSerialxCode = nSerialxCode * 3

    nInputxCode = ((nInputxCode ^ 2) * 6)
    nSerialxCode = (nSerialxCode << 2) + 0x4

def HundredTwentySecondFrom160():
    strkey = "TSSFTMEZDPKS"
    listKey = list(strkey)
    for i in range(0xffffffff):
        if i == 0:
            continue

        nKey = [i]
        nIndex = 0
        bFound = True
        while(nIndex < len(strkey)):
            c = rand(nKey) % 26
            if c != ord(listKey[nIndex]) - 0x40 - 1:
                bFound = False
                break
            nIndex += 1
            if(nIndex > 5):
                print(i)

        if (bFound):
            print("Found: key:  " + str(i))
            break

def nameAdd(strname, lenName, addNum):
    nRet = 1
    listlocalSerial = [
            'h', '1', '4', 'M', 'l', '0', 'x', '\n',
            '7', 'k', 'C', 'H', 'w', 'X', 'B', 'z', 'H', '\t', 
            'G', '8', 'i', 'N', '9', '+', 'w', 'b', '5', 'V', 'H', 'Z'
        ]
    nlocalLen = len(listlocalSerial)
    halfLocalLen = int(nlocalLen / 2)
    nOut = 1
    for cCharactor in strname:
        nChara = ord(cCharactor)
        nPreBackadd = nChara * nRet
        for index in range(halfLocalLen):
            v1 = ord(listlocalSerial[nlocalLen - index - 1]) - nChara % (index + 1)
            v2 = nPreBackadd + ord(listlocalSerial[index])
            nPreBackadd = v1 + v2
        nRet = addNum ^ (((nOut * nPreBackadd) << 8) & 0xffffffff)
        nOut += 1
    return nRet

def GetFilePos(strName, strCompany, listPos):
    nameLen = len(strName)
    companyLen = len(strCompany)
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

def ReadFileAndChangeMemory(pos, size):
    pass
    

def HundredTwentyFifthFrom160():
    #nLevel = int(input("Get level:   "))
    nLevel = 5

    if nLevel == 1:
        print("reg:  qJT62aWfviq0P57JGs2FelQkX")
    elif nLevel == 2:
        checkName = "12345678"#helloEnter()
        strCheckCode = ""
        lenName = len(checkName)
        if lenName < 5:
            return

        nAddName = 0
        listName = list(checkName)
        listName.append('\0')
        for i in range(lenName):
            nAddName = (i+1) * (nAddName + ord(listName[i + 1]))

        for i in range(lenName):
            strCheckCode += chr(int(nAddName / ord(listName[i])) % 0xA + 0x30)
        
        helloEnd(strCheckCode)

    elif nLevel == 3:
        checkName = "12345678"#helloEnter()
        strCheckCode = ""
        lenName = len(checkName)
        if lenName <= 5:
            return
        
        listName = list(checkName)
        nSib = 0
        nCheckCode = -2128125115
        for i in range(lenName):
            nCheckCode = (~nSib) * (i + 1) * ((i << 8) ^ (ord(listName[i]) + nCheckCode))
            if nCheckCode > 0:
                nCheckCode = nCheckCode & 0xffffffff
            else:
                nCheckCode = -1 * (-1 * nCheckCode) & 0xffffffff
            nSib += lenName

        print(nCheckCode)
    elif nLevel == 4:
        checkName = helloEnter()
        strCheckCode = ""
        lenName = len(checkName)

        nBackDec = 0
        nBackHex = 0
        for i in range(lenName):
            if i % 2 == 0:
                nBackHex = nameAdd(checkName, lenName, i + nBackDec)
            else:
                nBackDec = nameAdd(checkName, lenName, i + nBackHex)

        strCheckCode = str(nBackDec) + '-' + hex(nBackHex)[2:].upper()
        helloEnd(strCheckCode[::-1])

    elif nLevel == 5:
        checkName = "12345678910" #helloEnter()
        checkCompany = "companycom"
        lisFile = [ 0x4a00 ]
        GetFilePos(checkName, checkCompany, lisFile)
        print(lisFile)

    elif nLevel == 6:
        pass

def HundredTwentySixthFrom160():
    checkName = helloEnter()
    listCheckName = list(checkName)
    lenName = len(checkName)

    nLastAsc = ord(listCheckName[lenName - 1]) * lenName
    nAddName = 0
    for c in checkName:
        nAddName = nAddName + nLastAsc * ord(c)

    nAddName ^= 0x10
    nNamePre = nAddName ^ 0x6F
    nCheckCode = nNamePre + 47391895
    if nCheckCode % 10 != 8:
        nCheckCode = nCheckCode - nCheckCode % 10 + 18

    helloEnd(str(nNamePre) + "-" + str(nCheckCode))


def HundredTwentySeventhFrom160():
    checkName = helloEnter()
    nNameAdd = 0
    for c in checkName:
        nNameAdd += ord(c)
    nNameAdd += 0xA
    nNameAdd ^= 0x5e
    nNameAdd *= 238
    strNameAdd = str(nNameAdd).zfill(10)
    strCheckCode = ""

    nIndex =0
    for c in strNameAdd:
        strCheckCode += hex(nIndex ^ (nIndex*64) ^ ord(c))[2:].upper()
        nIndex+=1
    helloEnd(strCheckCode)

    
def HundredTwentyEighthFrom160():
    checkName = helloEnter()
    nNameDeal = ord(checkName[0:1].upper()) * len(checkName)
    nNameDeal = (nNameDeal << 0xc) + 0x3930e
    nCheckCode = nNameDeal - 0x14
    helloEnd(nCheckCode)


def HundredTwentyNinethFrom160():
    checkName = "123"#helloEnter()
    nInxSpec = 0
    nAdd = 0
    #answer = 8DCAF368
    # code stright
    for c in checkName:
        nInxSpec &= 0x00 
        nInxSpec += ord(c)
        nInxSpec = circular_shift_left(nInxSpec, 8)
        nAdd += nInxSpec
        nAdd &= 0xffffffff
    
    # reverse 
    nAnswer = 0x8DCAF368
    nZero = nAnswer & 0xff
    nFirst = (shift_arithmetic_right(nAnswer, 24) & 0xff) - (nAnswer & 0xff)
    nSecond = (shift_arithmetic_right(nAnswer, 16) & 0xff) - (shift_arithmetic_right(nAnswer, 24) & 0xff)
    nThird = (shift_arithmetic_right(nAnswer, 8) & 0xff) - (shift_arithmetic_right(nAnswer, 16) & 0xff)
    strCheckCode = chr(nZero) + chr(nFirst) +  chr(nSecond) + chr(nThird)
    helloEnd(strCheckCode)


def HundredThirtyFirstFrom160():
    print("Serial: 3Qr53pX")


def HundredThirtySecondFrom160():
    listPassCode = [
        0x71, 0x18, 0x59, 0x1b, 0x79, 0x42, 0x45, 0x4c
    ]
    nXorKey = 0
    for coXOr in listPassCode:
        nXorKey ^= coXOr
    
    strCheckCode = ""
    for cxXor in listPassCode:
        strCheckCode += chr(cxXor ^ 0x32 ^ nXorKey)

    helloEnd(strCheckCode)


def HundredThirtyFifthFrom160():
    checkName = helloEnter()
    strCheckCode = ""
    for c in checkName:
        strCheckCode = str(ord(c))[-2:] + strCheckCode
    helloEnd(strCheckCode)

def HundredThirtySixthFrom160():
    checkName = "kedaya"#helloEnter()
    lenCheckName = len(checkName)
    listCheckName = list(checkName)
    strModCheck = "31415926535897932384"
    listModeCheck = list(strModCheck)
    strCheckCode = ""
    
    for i in range(lenCheckName):
        singleCode = 2 * (ord(listCheckName[i]) % ord(listModeCheck[i]))
        if(singleCode > 123):
            singleCode -= 26
        if(singleCode < 65):
            singleCode = 130 - singleCode
        if(singleCode > 91 and singleCode < 97):
            singleCode = singleCode % 10 + 48
        strCheckCode += chr(singleCode)

    helloEnd(strCheckCode)


def HundredThirtySeventhFrom160():
    print("Serial: SSSSSS")

def HundredThirtyNinethFrom160():
    nFixNum = 0x20A9
    with open("139.dat", 'wb') as fp:
        while(nFixNum > 0xff):
            nFixNum -= 0xff
            byte = struct.pack('B', 0xff)
            fp.write(byte)
        byte = struct.pack('B', nFixNum)
        fp.write(byte)
        byte = struct.pack('B', 0x00)
        fp.write(byte)

def HundredFortythFrom160():
    strfile = 'Runtime Error: 12FF:024'
    with open("140.dat", 'w') as fp:
        fp.write(strfile)
    
    checkName = "kedaya"#helloEnter()
    nCheckCode = 0
    nSunPre = 0
    nIndex = 1
    for c in checkName:
        nSunPre -= ord(c)
        if nSunPre < 0:
            nSunPre += 0x100
        nSunPre += nIndex
        nCheckCode += nSunPre
        nIndex += 1
    while nCheckCode < 0x438d:
        nCheckCode += 0x45e6

    checkCode = str(nCheckCode)[0:2] + "-" + str(nCheckCode)[2:3] + "-" + str(nCheckCode)[3:]
    helloEnd(checkCode)

def HundredFortythThirdFrom160():
    print("UnlockKey: CrackMe [id:9] by tC... .")

def HundredFortythSixthFrom160():
    checkArr = [
        0x3a, 0xd9, 0xc4, 0xc9, 0xba, 0xbf, 
        0xde, 0x7d, 0x44, 0xcf, 0xe2, 0xd9,
        0xEA, 0x49, 0xD2, 0xDD, 0xDE, 0x8F
    ]
    strCheckCode = ""

    checkArr = checkArr[::-1]
    nIndex = 0
    for nIndex in range(len(checkArr)):
        nTemp = checkArr[nIndex]+ nIndex + 1 - 8
        nTemp = int (nTemp / 2)
        nTemp ^= 3
        checkArr[nIndex] = nTemp
        strCheckCode += chr(nTemp)
        
    print(strCheckCode)
        
def HundredFortythSeventhFrom160():
    checkName = "kedaya"#helloEnter()
    checkSerial = ""
    checkReg = ""

    for c in checkName:
        checkSerial += chr(ord(c) + 3)
        checkReg += chr(ord(c) - 3)
    
    print(checkSerial)
    print(checkReg)

def HundredFortythEighthFrom160():
    nLicense = 2 # single
    if nLicense == 1:
        checkName = "kedaya"#helloEnter()
        checkCode = checkName[::-1]
        helloEnd(checkCode)
    else:
        checkName = "abcde"#helloEnter()
        checkName = checkName[::-1]
        checkCode = ""
        for c in checkName:
            checkCode += chr(ord(c) + 8)
        helloEnd(checkCode)

def HundredFiftySecondFrom160():
    hMd5 = hashlib.md5()
    strMd5Init = 0x12345678#9ABCDEF0#FEDCBA9876543210
    byte = struct.pack('IIII', 0x12345678, 0x9ABCDEF0, 0xFEDCBA98, 0x76543210)
    
    checkName = "solly"
    while len(checkName) < 0x40:
        checkName += checkName
    while len(checkName) > 0x40:
        checkName = checkName[:-1]
    checkName = chr(0) + checkName[:-1]
    hMd5.update(checkName.encode(encoding='UTF-8'))
    strMd5 = hMd5.hexdigest()
    nCheckFirst = int(strMd5[0:8], 16) + int(strMd5[24:], 16) - int(strMd5[8:16], 16) - int(strMd5[16:24], 16)
    print(nCheckFirst)
    pass

def HundredFiftyThirdFrom160():
    print("key: aa70068")

def HundredFiftyFourthFrom160():
    checkMidte = "PhroZenQ"
    listCheckMidte = list(checkMidte)
    checkName = "aaaa"##helloEnter()
    nIndex = 0
    while len(checkName) < 8:
        checkName += str(nIndex)
        nIndex += 1

    strMiddle = ""
    listCheckName = list(checkName)
    for i in range(4):
        nTemp = ord(listCheckName[i]) + ord(listCheckName[7-i])
        listCheckName[i] = nTemp#nTemp^ord(listCheckMidte[i])
        #listCheckName[i + 4] = nTemp^ord(listCheckMidte[i+4])

    listCheckName[4:8] = listCheckName[0:4]
    for i in range(8):
        listCheckName[i] ^= ord(listCheckMidte[i])

    nRol = listCheckName[0]
    nXor = listCheckName[5] + listCheckName[6]*0x100 + listCheckName[7]*0x10000
    nAA = listCheckName[1] + listCheckName[2]*0x100 + listCheckName[3]*0x10000 + listCheckName[4]*0x1000000

    for i in range(32):
        nTemp = circular_shift_right(nAA, i)
        if(nTemp % 32 != i):
            continue
        
        nTemp = nTemp ^ nXor
        nCheckCode = circular_shift_right(nTemp, nRol)
        print(nCheckCode)
    #ror(nAA, (nXor ^ rol(nPass, nRol))) == nXor ^ rol(nPass, nRol)

def HundredFiftySixthFrom160():
    strfile = '3867771216'
    with open("crack.dat", 'w') as fp:
        fp.write(strfile)
        
    checkName = "aaaa"#helloEnter()
    checkOrga = "bbb"#helloEnter()
    listCheckName = list(checkName)
    listOrga = list(checkOrga)

    if len(checkOrga) > len(checkName):
        return 

    nAddAll = 0
    for index in range(len(checkOrga)):
        nAddAll += ord(listCheckName[index]) * ord(listOrga[index])

    helloEnd(nAddAll) 

def HundredFiftySeventhFrom160():
    strfile = '3624563226'
    with open("crack.dat", 'w') as fp:
        fp.write(strfile)

    checkName = "aaaa"#helloEnter()
    checkOrga = "1234"#helloEnter()
    if(len(checkName) < 3 or len(checkOrga) <3):
        return
    
    nCheckCode = 0
    nNameFirst = ord(checkName[0:1])
    nOrgaFirst = ord(checkOrga[0:1])
    while nNameFirst < 0x100:
        nTempName = nNameFirst
        nTempOrga = nOrgaFirst
        if nNameFirst & 0x80:
            nTempName = 0xffffff00 ^ nTempName
        if nOrgaFirst & 0x80:
            nTempOrga = 0xffffff00 ^ nTempOrga

        nCheckCode += (getIntFromUnint(nTempName) * getIntFromUnint(nTempOrga))
        nNameFirst += 1
        nOrgaFirst += 1

        nOrgaFirst &= 0xff
    helloEnd(nCheckCode)

def HundredFiftyEighthFrom160():
    arrMonthKey = [
        0, 0x39, 0x38, 0x30, 0x33, 0x44, 0x32, 0x46, 0x37, 0x34, 0x30, 0x34, 0x45
    ]
    arrDayKey = [
        0, 0x46, 0x33, 0x41, 0x34, 0x42, 0x46, 0x33, 0x42, 0x30, 0x35,
        0x30, 0x33, 0x46, 0x42, 0x38, 0x42, 0x43, 0x42, 0x34, 0x46,
        0x34, 0x39, 0x38, 0x30, 0x33, 0x44, 0x35, 0x43, 0x37, 0x34, 0x30
    ]
    strMul7020 = "Etn5Pnc5AXi1DFlkYqnujsXNmvHdbcrqOoT8aaV5DkaymMRkPkoQ."
    strMul7058 = "fQObVwNOankJ5skqJvae3Ae5jdoETu5n02J6Ez85430PNSDAPjDrYgFaze9VDRjq"
    checkName = "aaaa"#helloEnter()
    checkGroup = "bbbb"#helloEnter()

    mMonth = datetime.date.today().month
    mDay = datetime.date.today().day
    nPreCodeFirst = arrMonthKey[mMonth] * arrDayKey[mDay]

    nPreCodeSecond = 0
    for index in range(len(checkName)):
        if index == 0:
            continue
        nPreCodeSecond += index * ord(strMul7020[index-1:index]) * ord(strMul7058[index-1:index]) * ord(checkName[index-1:index])

    for index in range(len(checkGroup)):
        if index == 0:
            continue
        nPreCodeSecond += index * ord(strMul7020[index-1:index]) * ord(strMul7058[index-1:index]) * ord(checkGroup[index-1:index])
    print(nPreCodeFirst + nPreCodeSecond)

def HundredFiftyNinethFrom160():
    arrSerial = [
        0,0,0,0,0,0,0,0,0,0
    ]
    arrSerial[0] = chr(0x54 ^ 29)
    arrSerial[1] = chr(0x49 ^ 13)
    arrSerial[2] = chr(0x44 ^ 7)
    arrSerial[3] = chr(0x39 ^ 13)

    arrSerial[6] = chr(0x54 ^ 17)
    arrSerial[7] = chr(0x52 ^ 6)
    arrSerial[8] = chr(0x45 ^ 7)

    arrSerial[4] = chr(0x39 ^ 9)
    arrSerial[9] = chr(0x53 ^ 31)
    
    mYear = datetime.date.today().year
    mMonth = datetime.date.today().month
    mDay = datetime.date.today().day
    mHour = datetime.datetime.now().hour
    mMin = datetime.datetime.now().minute
    checkLastFour = mMin * mHour + mDay * mMonth + mYear

    print(arrSerial)

def HundredSixtyFrom160():
    pass

def helloEnter():
    checkname = input("Please Enter Your Name!\n")
    print("checksName: \t" + checkname)
    print("\n")
    print("SerialName: \t")
    return checkname

def helloEnd(sierail):
    print(sierail)
    print("\n")

def main():
    HundredFiftyNinethFrom160()

if __name__ == '__main__':
    main()
