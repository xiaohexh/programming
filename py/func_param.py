#!/usr/bin/python
# Filename: func_param.py

def max(a, b):
	if a < b:
		return b
	else:
		return a

x = 5
y = 7
max_num = max(x, y)
print max_num

# default parameter
def sum(a, b = 1, c = 2):
	return a + b + c

print sum(1)
print sum(2)
print sum(1, 2, 3)
print sum(c = 1, a = 2)
print sum(c = 1, a = 2, b = 3)

# packing parameters
def mul(*params):
	print type(params)
	ret = 1
	for param in params: 
		ret *= param
	return ret

print mul(1, 2, 3)

print '=' * 30

# pass more than one parameter
def store(*person_info):
	print 'Name:%s' % person_info[0]
	print 'Age:%d' % person_info[1]
	print 'Gender:%s' % person_info[2]

store('Andy', 23, 'M')

print '=' * 30

# pass 
def display(persons):
	i = 1
	for person in persons:
		print 'No.%d information:' % i
		print 'Name:%s' % person[0]
		print 'Age:%d' % person[1]
		print 'Gender:%s' % person[2]
		i += 1

persons = [['Chris', 23, 'M'], ['Jean', 34, 'F'], ['Harry', 45, 'M']]
display(persons)

def mutable(x, y):
	x[0] += 100
	y += 100


a = [3]
b = 3
mutable(a, b)
print a, b

