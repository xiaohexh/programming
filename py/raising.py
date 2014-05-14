#!/usr/bin/python
# Filename: raising.py

import sys

class ShortInputException(Exception):
	'''A user-defined exception class'''
	def __init__(self, length, atleast):
		Exception.__init__(self)
		self.length = length
		self.atleast = atleast

if __name__ == '__main__':
	
	atleast = 3

	try:
		s = raw_input('Enter sth -->')
		if len(s) < atleast:
			raise ShortInputException(len(s), atleast)
	except EOFError:
		print '\nWhy did you do an EOF on me?'
		sys.exit()
	except ShortInputException, x:
		print '\nException occured\nLength of %s is shorter than at least(%d)' % (s, atleast)
	else:
		print 'No exception was raised.'
