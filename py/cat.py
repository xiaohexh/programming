#!/usr/bin/python
# Filename: cat.py

import sys

def readfile(filename):
	f = file(filename)
	while True:
		line = f.readline()
		if 0 == len(line):
			break

		print line,

	f.close()


if __name__ == '__main__':

	if len(sys.argv) < 2:
		print 'No action specified.'
		sys.exit()

	print 'parameter list:\n', sys.argv[1:]

	if sys.argv[1].startswith('--'):
		option = sys.argv[1][2:]

		if option == 'version':
			print 'Version 1.2'
		elif option == 'help':
			print '''\
			This program prints files to the standard output.
			Any number of files can be specified.
			Options include:
				--version : Prints the version number
				--help    : Display this help'''
		else:
			print 'Unknow option'

		sys.exit()
	else:
		for filename in sys.argv[1:]:
			readfile(filename)
