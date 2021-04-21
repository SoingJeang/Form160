'''
Author: your name
Date: 2021-03-06 01:02:10
LastEditTime: 2021-04-21 13:18:41
LastEditors: Please set LastEditors
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