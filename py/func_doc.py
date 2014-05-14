#!/usr/bin/python
# Filename: func_doc.py

def print_max(x, y):
	'''Prints the maximum of x and y.

	The two values must be integer.'''
	x = int(x)
	y = int(y)

	if x > y:
		return x
	else:
		return y

print print_max(3, 5)
print print_max.__doc__
