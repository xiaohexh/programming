#!/bin/python

import os

for file_name in os.listdir('.'):
	if -1 == file_name.find('.c'):
		continue
	new_name = file_name + 'pp'
	os.rename(file_name, new_name)
