#!/usr/bin/python

import os

dbName = 'gregs_list'
update_cmd = 'update nut_list set doughnut_cost = 2.3 where doughnut_name = \'Apple\''
sql_cmd = 'mysql -h localhost -uroot -proot000 ' + dbName \
		  + ' -e ' + '"' + update_cmd + '"'
print sql_cmd
if os.system(sql_cmd) == 0:
	print 'execute sql sentence success'
else:
	print 'execute sql sentence failed'
