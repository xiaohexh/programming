#!/usr/bin/python
# Filename: for.py

for i in range(4):
	print i,
print

s = 'abcdefghijklmn'

for i in range(0, len(s), 2):
	print s[i],
print

a = [1, 2, 3]
b = [7, 8, 9]
c = ['sh', 'bj', 'hk']
for (ta, tb, tc) in zip(a, b, c):
	print (ta, tb, tc)
