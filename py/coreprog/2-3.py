#!/usr/bin/python

def sum(a, b):
	print '%d + %d = %d' % (a, b, a + b)

def sub(a, b):
	print '%d - %d = %d' % (a, b, a - b)

def mul(a, b):
	print '%d * %d = %d' % (a, b, a * b)

def div(a, b):
	print '%d / %d = %d' % (a, b, a / b)

def mod(a, b):
	print 'mod of %d / %d is %d' % (a, b, a // b)

def pow(a, b):
	print '%dth power of %d is %d' % (a, b, a ** b)

def menu():
	print '1.sum\t\t2.sub'
	print '3.mul\t\t4.div'
	print '5.mod\t\t6.pow'

if __name__ == '__main__':
	a = 5
	b = 3
	while True:
		menu()
		choice = raw_input('Enter your choice(\'q/Q to quit\'):')
		if choice == 'q' or choice == 'Q' or choice == 'quit' or choice == 'Quit':
			break
		choice = int(choice)
		if choice == 1:
			sum(a, b)
		elif choice == 2:
			sub(a, b)
		elif choice == 3:
			mul(a, b)
		elif choice == 4:
			div(a, b)
		elif choice == 5:
			mod(a, b)
		elif choice == 6:
			pow(a, b)
		else:
			print 'Invalid input'
