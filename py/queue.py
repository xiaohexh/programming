#!/usr/bin/python

import Queue

q = Queue.Queue(10)
for i in range(10):
	myData = 'A'
	if q.full():
		break
	q.put(myData)
	myData = 'B'

print 'Queue size:%d' % q.qsize()
while not q.empty():
	print q.get(),

print q.get(False)
