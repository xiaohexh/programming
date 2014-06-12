#!/usr/bin/python
# operate on file using linecache lib

import linecache
import random 

fileName = 'for_file_op_test'
lines = linecache.getlines(fileName)    # get all lines
for line in lines:   # lines is a list
	print line,

print '=' * 20

lineNum = len(lines)
print 'There\'re %d lines in file %s' % (lineNum, fileName)
selLine = random.randint(0, lineNum - 1)
print 'select line no:%d' % (selLine + 1)
line = linecache.getline(fileName, selLine + 1)
print line

randLine = random.choice(lines)  # random.choice method used to select a element from a sequence
print 'select a line randomly:%s' % randLine

nums = (1, 45, 21, 78)
randNum = random.choice(nums)
print 'select random number from a tuple:%d' % randNum

if 'v1p@w1fj#CN' == 'v1p@w1fj#CN':
	print 'True'
