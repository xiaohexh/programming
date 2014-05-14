#!/usr/bin/python
# Filename: backup_ver2.py

import os
import time

source = ['./backup_for_ver1', 'backup_ver2.py']

target_dir = './'

today = target_dir + time.strftime('%Y%m%d')

now = time.strftime('%H%M%S')

if not os.path.exists(today):
	os.mkdir(today)
	print 'Successfully create directory'

target = today + os.sep + now + '.zip'

zip_cmd = 'zip -qr %s %s' % (target, ' '.join(source))

if os.system(zip_cmd) == 0:
	print 'Successfully backup'
else:
	print 'Backup failed'
