'''
Author: your name
Date: 2021-03-06 01:02:10
LastEditTime: 2021-07-01 14:22:41
LastEditors: SoingJeang
Description: In User Settings Edit
FilePath: \Form160\commonForm.py
'''
import binascii

def is_number(s):
    """
    @description  :
        Check is a number or not
    ---------
    @param  :
        int num
    -------
    @Returns  :
        bool for result
    -------
    """
    
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

    #123456789abcdefg000
def big_smaill_end_convert(data):
    """
    @description  :
        revert big endian to small endiam or small to big
    ---------
    @param  :
        byte_value: byte
    -------
    @Returns  :
        byte_value byte
    -------
    """
    return binascii.hexlify(binascii.unhexlify(data)[::-1])

def circular_shift_left(int_value, k, bit = 32):
    """
    @description  :
        rol, 
    ---------
    @param  :
        int_value: toTran
        k: size
        bit: for bin or Hex...
    -------
    @Returns  :
        back TranedValue
    -------
    """
    
    bit_string = '{:0%db}' % bit
    bin_value = bit_string.format(int_value)
    bin_value = bin_value[k:] + bin_value[:k]
    int_value = int(bin_value, 2)
    return int_value

def circular_shift_right(int_value, k, bit = 32):
    """
    @description  :
        ror, default is 32bit
    ---------
    @param  :
        int_value: toTran
        k: size
        bit: for bin or Hex...
    -------
    @Returns  :
        back TranedValue
    -------
    """

    bit_string = '{:0%db}' % bit
    bin_value = bit_string.format(int_value)
    bin_value = bin_value[bit-k:] + bin_value[:bit-k]
    int_value = int(bin_value, 2)
    return int_value

def shift_arithmetic_left(int_value, k, bit = 32):
    pass

def shift_arithmetic_right(int_value, k, bit = 32):
    bit_string = '{:0%db}' % bit
    bin_value = bit_string.format(int_value)

    bin_value = bin_value[:1] + bin_value[:1]* k + bin_value[1:bit-k]
    
    int_value = int(bin_value, 2)
    return int_value

def extend_Gcd(m, b):
    if m < b:
        t = m
        m = b
        b = t
    x1, x2, x3 = 1, 0, m
    y1, y2, y3 = 0, 1, b
    while True:
        if y3 == 0:
            return 'None'
            break
        elif y3 == 1:
            return y2 % m
            break
        else:
            Q = x3 // y3
            t1, t2, t3 = x1 - Q * y1, x2 - Q * y2, x3 - Q * y3
            x1, x2, x3 = y1, y2, y3
            y1, y2, y3 = t1, t2, t3

def fast_power_with_mod(base, power, modNum):
    result = 1
    while(power > 0):
        if power & 1:
            result = base * result % modNum
        base = base * base % modNum
        power = int(power / 2)
    return result

def rand(key):
    retValue = key[0] * 0x343fd + 0x269ec3
    key[0] = retValue
    retValue = (retValue >> 0x10) & 0x7fff
    return retValue

def getIntFromUnint(nUnint):
    if(nUnint & 0x80000000):
        nUnint ^= 0xffffffff
        return -1 *(nUnint + 1)
    else:
        return nUnint