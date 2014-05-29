#/usr/bin/python
# Filename: thread_exe.py

import random
import time
import threading

def threadFunc():
	for i in range(10):
		print 'ThreadFunc-%d' % i
		time.sleep(random.randrange(0, 2))

class ThreadClass(threading.Thread):
	def __init__(self):
		threading.Thread.__init__(self);
		print 'thread id:%d' % self.ident

	def run(self):
		for i in range(10):
			print 'ThreadClass - %d' % i
			time.sleep(random.randrange(0, 2))

if __name__ == '__main__':
	tFunc = threading.Thread(target = threadFunc)
	print 'tFunc thread id:%d' % tFunc.ident
	tCls = ThreadClass()
	tFunc.start()
	tCls.start()
