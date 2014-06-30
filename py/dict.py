#!/usr/bin/python

dic = {}
dic['Tom'] = 90
dic['Tom'] = 80
dic['Andy'] = 100
dic['Chris'] = 190
print dic

for key in dic:
	print dic[key],

print

print 'keys:'
for key in dic.keys():
	print key,

print

print 'values:'
for value in dic.values():
	print value,

print

print 'items:'
for item in dic.items():
	print item,

if 'Tom' in dic.keys():
	del dic['Tom']
	print '\nafter delete Tom:', dic.items()

print 'clear all the items in dic'
dic.clear()
print dic
