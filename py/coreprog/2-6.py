#!/usr/bin/python

number = int(raw_input('Enter a number:'))
if number > 0:
	print '%d is positive' % number
elif number == 0:
	print 'Zero'
else:
	print '%d is negative' % number

