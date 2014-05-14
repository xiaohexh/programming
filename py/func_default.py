#!/usr/bin/python
# Filename: func_default.py

def welcome(name, times = 1):
	print name * times

name = 'Chris'
welcome(name)
name = 'Andy'
welcome(name, 3)
