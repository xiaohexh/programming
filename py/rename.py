#!/bin/python

import os

for file_name in os.listdir('.'):
	print file_name
	if -1 == file_name.find('.tmp'):
		continue
	tmplist = file_name.split('.')
	new_name = tmplist[0] + '.' + tmplist[1]
	os.rename(file_name, new_name)
