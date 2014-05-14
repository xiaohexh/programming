#!/usr/bin/python
# Filename: backup_ver1.py

import os
import time

source = ['./backup_for_ver1', 'backup_ver1.py']

target_dir = './'

target = time.strftime('%Y%m%d%H%M%S') + '.zip'

zip_cmd = 'zip -qr %s %s' % (target, ' '.join(source))

if os.system(zip_cmd) == 0:
	print 'Successful backup to', target
else:
	print 'Backup Failed'
