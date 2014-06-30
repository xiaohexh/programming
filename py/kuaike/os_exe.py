#!/usr/bin/python

import os
import shutil

dir_path = '/tmp/py_test'
file_name = ''
new_name = 'new_name'

if os.path.exists(dir_path):
	print '%s is already exist' % dir_path
	file_list = os.listdir(dir_path)
	print type(file_list)
	print 'file under dir:%s is as follows:' % dir_path
	print file_list
	file_name = file_list[0]
	print os.getcwd()
else:
	print '%s is not exist, and create it' % dir_path
	os.mkdir(dir_path)

file_name = dir_path + '/' + file_name
print 'copy %s to current working directory' % file_name
shutil.copy(file_name, os.getcwd())
if os.path.isfile(file_name):
	print 'copy success'
else:
	print 'copy failed'

print 'delete directory %s' % dir_path
file_list = os.listdir(dir_path)
for f in file_list:
	f = dir_path + '/' + f
	print 'delete file %s' % f
	os.remove(f)
os.rmdir(dir_path)

file_name = 'test3'
print 'delete file %s' % file_name
os.remove(file_name)
