#!/usr/bin/python

from ctypes import *

ARRAY_NUMBER = 20
STR_LEN = 20

# define type
INTARRAY20 = c_int * ARRAY_NUMBER
CHARARRAY20 = c_char * STR_LEN

# define struct
class StructTest(Structure):
	_fields_ = [
	("number", c_int),
	("pChar", c_char_p),
	("str", CHARARRAY20),
	("iArray", INTARRAY20)
	]

#define type
STRUCTTESTARRAY10 = StructTest * 10

class StructTestArray():
  _fields_ = [
  ("structTest", STRUCTTESTARRAY10)
  ]

# load so and get the function object
ll = cdll.LoadLibrary
lib = ll('./sum.so')
print lib.foo(1, 3)
lib.Print(7)

GetStructInfo = lib.GetStructInfo;
# set the return type
GetStructInfo.resttype = c_char_p;
# set the argtypes
GetStructInfo.argtypes = [POINTER(StructTest)]

totalnum = lib.totalNum
num = totalnum()
print 'totalnum:', int(num)

index = 0
while index < int(num):

    objectStruct = StructTest()
    # invoke api GetStructInfo
    retStr = GetStructInfo(byref(objectStruct))

    #check result
    print "number:", objectStruct.number
    print "pChar:", objectStruct.pChar
    print "str:", objectStruct.str
    for i, val in enumerate(objectStruct.iArray):
        print 'Array[i]:', val
    print retStr
    index = index + 1
    print 'index:', index
