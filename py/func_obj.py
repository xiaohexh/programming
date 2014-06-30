#!/usr/bin/python

func = lambda x, y:x + y
print func(4, 5)

def Test(f, x, y):
	print 'parameter:%d %d' % (x, y)
	print f(x, y)

mul = lambda x, y:x * y

Test(mul, 4, 5)

# usage of map
src = [1, 3, 5, 7]
dst = map(lambda x:x ** 2, src)
print 'source:', src
print 'dest:',dst
