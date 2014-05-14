#!/usr/bin/python
# Filename: finally.py

import time

try:
	f = file('poem.txt')
	while True:
		line = f.readline()
		if 0 == len(line):
			break

		time.sleep(2)
		print line,

finally:
	f.close()
	print 'close file finally'
