#!/usr/bin/python

import MySQLdb
import thread

conn=MySQLdb.connect(host='localhost',user='root',passwd='root000',port=3306)
cur=conn.cursor()
	     
conn.select_db('umonitor2')
		 
count = cur.execute('select * from test where name = \'chris\'')
print 'there has %s rows record' % count
				 
if count != 0:
	result = cur.fetchone()
	print 'result:', result   # fetch first record
	print 'result:', result[2] # fetch third column of record (column index start with 0)

print '=='*10

'''
results = cur.fetchmany(2)
for r in results:
	print r
	'''

cur.close()
conn.close()
