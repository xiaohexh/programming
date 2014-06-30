#!/usr/bin/python

lines = ['u load balance', 'Technology company', 'fire hypervisor']

import os
import glob

file_name = 'tmp.txt'

if not os.path.isfile(file_name):
	fp = open(file_name, 'a')
	for line in lines:
		print line
		fp.write(line)
		fp.write('\n')
	fp.close()
	
if os.path.isfile(file_name):
	fp = open(file_name, 'r')
	contents = fp.readlines()
	for line in contents:
		print line,
	fp.close()

file_name = '/home/xiaohe/tmp.txt'
print os.path.dirname(file_name)
print os.path.basename(file_name)
info = os.path.split(file_name)
print info

dirname = os.path.dirname(file_name)
dirname += '/*'
file_list = glob.glob(dirname)
print file_list


