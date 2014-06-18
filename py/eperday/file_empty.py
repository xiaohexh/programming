#!/usr/bin/python

import time
import os

file_name = 'test.log'

curr_time = 1234567
cpu_time = 157943473289

time_list = ['12345', '67890', '13579', '24680']

if not os.path.isfile(file_name) or 0 == os.path.getsize(file_name):
	with open(file_name, 'w') as fp:
		data = str(curr_time) + ':' + str(cpu_time)
		fp.write(data)

with open(file_name, 'r') as fp:
	data = fp.read()
	print data
	(curr_str, cpu_str) = data.split(':')
	print curr_str
	print cpu_str

'''
if os.path.exists(file_name):
	with open(file_name, 'r') as fp:
		data = fp.read()
		if len(data) == 0:
			print 'file exist, but content is empty'
		'''

file_name = "test_time.txt"
if not os.path.isfile(file_name):
	with open(file_name, 'w') as fp:
		fp.write("Hello")

time_str = ''
for item in time_list:
	time_str += item + '\n'
	print time_str
