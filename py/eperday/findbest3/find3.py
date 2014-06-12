#!/usr/bin/python

# find best 3 scores of each student
# scores stored in each .txt file

import os

os.chdir("/home/xiaohe/programming/py/eperday/findbest3")

# get score from file
def get_score(file_name):
	try:
		with open(file_name) as f:
			data = f.readline()
			time_list = data.strip().split(',')
			print time_list
			return time_list
	except IOError as ioerr:
		print 'File Error %s' % str(ioerr)
		return None

# format time format as 'min.second'
def modify_time_format(time_string):
	if '-' in time_string:
		splitter = '-'
	elif ':' in time_string:
		splitter = ':'
	else:
		splitter = '.'

#(mins, secs) = time_string.split(splitter)
	min_sec_list = time_string.split(splitter)
	if len(min_sec_list) < 2:
		print min_sec_list
	return (min_sec_list[0] + ',' + min_sec_list[1])

# return three scores
def get_prev_three(file_name):
	new_list = [modify_time_format(each_t) for each_t in get_score(file_name)]
	delete_repetition = set(new_list)
	in_order = sorted(delete_repetition)
	return in_order[0:3]

if __name__ == '__main__':
	print get_prev_three('andy.txt')
