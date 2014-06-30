#!/usr/bin/python

def feb(i, j, n):
	print i, j,
	for k in range(n):
		print j,
		i, j = j, i + j

feb(0, 1, 6)
print

L = [x**2 for x in range(4)]
print L

xl = [2, 3, 5]
yl = [9, 10, 12]
L = [x * y for (x, y) in zip(xl, yl) if y <= 10]
print L
