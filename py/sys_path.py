#!/usr/bin/python
# Filename: sys_path.py

import sys
import random

print 'Arguments as follows:'
for arg in sys.argv:
	print arg,

num = len(sys.argv)
print '\nargvs number:', num

if num == 1:
	print 'sys.argv[0]:', sys.argv[0]
else:
	select = random.randrange(1, num)
	print 'sys.argv[%d]:%s' % (select, sys.argv[select])

print '\nThe PYTHONPATH is', sys.path
