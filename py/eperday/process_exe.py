#!/usr/bin/python

import os
import time
from multiprocessing import Process,Queue,Lock

gCommonData = ['SH', 'BJ', 'HK']
lock = Lock()
 
def foo(name, interval):   
	time.sleep(1)
	print 'Hello:%s' % name
	print os.getppid() # get parent process id
	print os.getpid()
	lock.acquire()
	print gCommonData[0]
	time.sleep(interval)
	lock.release()

process_list = []
		     
if __name__ == '__main__':
	names = ['J', 'A', 'C']
	index  = 3
	for name in names:
		p = Process(target = foo, args = (name, index))
		p.start()
		process_list.append(p)
		index += 1
      
	time.sleep(5)
	for j in process_list:
		j.join()
