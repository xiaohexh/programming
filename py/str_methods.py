#!/usr/bin/python
# Filename: str_methods.py

name = 'Swaroop'

if name.startswith('Sw'):
	print 'Yes, stats with \'Sw\''

if 'oo' in name:
	print 'Yes, \'oo\' is in name'

delimiter = '_*_'
mylist = ['Brazil', 'China', 'Indian']
country = delimiter.join(mylist)
print country
