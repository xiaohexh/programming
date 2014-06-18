#!/usr/bin/python

len = 13
HOST_NUM = 3

def Deal(start, end):
	print 'start:%d, end:%d' % (start, end)

if len < HOST_NUM:
	Deal(0, len - 1)
else:
	tmp_0 = len / HOST_NUM
	tmp_1 = len % HOST_NUM
	i = 0
	start = 0
	while i < tmp_0:
		Deal(start, start + HOST_NUM - 1)
		start += HOST_NUM
		i += 1

	if tmp_1 != 0:
		Deal(HOST_NUM * tmp_0, len - 1)

