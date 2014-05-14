#!/usr/bin/python
# Filename: using_tuple.py

zoo = ('monkey', 'panda', 'tiger', 'lion')
print len(zoo)
new_zoo = ('fox', 'horse', zoo)
print len(new_zoo)
print new_zoo[2][1]
