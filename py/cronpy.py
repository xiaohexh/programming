#!/usr/bin/python
#coding: utf-8

import os
import time
import smtplib
from email.mime.text import MIMEText
from email.header import Header

fp = open('/tmp/cron.txt', 'a+')
timestr = time.strftime('%Y-%m-%d/%H:%M:%S', time.localtime(time.time())) 
fp.write(timestr)
fp.write(' Hello\n')
fp.close()

#os.system('"uwarn@ucloud.cno')
cmd = '/root/ums/UMSAccess/sendemail.sh xiaohexh@hotmail.com "Hello" \'I am testing\' "uwarn@xiaohe.cn" "uwarn" '
print cmd
