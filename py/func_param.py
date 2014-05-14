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
