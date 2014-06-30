#!/usr/bin/python

def getPerInfo(name):
	name = 'Andy'
	age = 23
	return (name, age)

if __name__ == '__main__':
	(name, age) = getPerInfo('Andy')
	print name, age

