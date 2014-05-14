#!/usr/bin/python
# Filename: backup_ver3.py

import os
import time

source = ['./backup_for_ver1', 'backup_ver3.py']

target_dir = './'

today = time.strftime('%Y%m%d')

now = time.strftime('%H%M%S')

comment = raw_input('Enter a comment:')

if len(comment) == 0:
	target = target_dir + today + os.sep + now + '.zip'
else:
	target = target_dir + today + os.sep \
			 + comment.replace(' ', '_') + '_' + now + '.zip'

if not os.path.exists(today):
	os.mkdir(today)

zip_cmd = 'zip -qr %s %s' % (target, ' '.join(source))

if os.system(zip_cmd) == 0:
	print 'Backup successfully'
else:
	print 'Backup failed'
