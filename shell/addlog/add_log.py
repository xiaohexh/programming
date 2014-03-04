#!/bin/python

import os

for file_name in os.listdir('.'):
    if -1 == file_name.find('cpp'):
	      continue

    file_obj = open(file_name, 'r')
    tmp_file_name = file_name + '.tmp'
    file_ret = open(tmp_file_name, 'w')
    while True:
		    line = file_obj.readline()
		    if not line:
			      break
		    if -1 != line.find('{') and line.startswith('int') or line.startswith('double') or line.startswith('void') or line.startswith('float'):
			      new_line = '\tDEBUG("==========' + line.strip('\n') + '=========%d", 1);\n'
			      line += new_line
			      file_ret.write(line)
		    else:
			      file_ret.write(line)
