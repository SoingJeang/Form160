import numpy
import datetime
import random
import binascii
import struct
import random
import string

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

def SixthForm160():
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

def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        pass
 
    try:
        import unicodedata
        unicodedata.numeric(s)
        return True
    except (TypeError, ValueError):
        pass
 
    return False

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

#123456789abcdefg000
def big_smaill_end_convert(data):
    return binascii.hexlify(binascii.unhexlify(data)[::-1])

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

def strUpperOrLow(data, isUpper):
    for _char in data:
        if isUpper:
            if _char >= 'a' and _char <= 'z':
                _char = _char

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
    thirtythFourthFrom160()

if __name__ == '__main__':
    main()