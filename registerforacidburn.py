import numpy
import datetime

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
    ForteenthForm160()

if __name__ == '__main__':
    main()