#!/usr/bin/python

import os

CPU_TIME_DIR_PREFIX = '/tmp/monitor/'

def Print():
	print 'Hello'
	return 1

def Foo():
	if Print() < 0:
		print 'World'
	else:
		print 'Main'

if __name__ == '__main__':
	if not os.path.exists(CPU_TIME_DIR_PREFIX):
		os.mkdir(CPU_TIME_DIR_PREFIX)
	filename = CPU_TIME_DIR_PREFIX + 'cpu_time.txt'
	if os.path.isfile(filename):
		print 'Ok'
	else:
		print 'not'
	Foo()
