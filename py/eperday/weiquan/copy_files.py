#!/usr/bin/python

import os
import os.path

fold_capacity = 20

def copy_files(src_dir, dst_dir):
	count = 0
	current_folder = ''

	for item in os.listdir(src_dir):
		abs_item = os.path.join(src_dir, item)
		if os.path.isfile(abs_item):
			count += 1
			if count % fold_capacity == 1:
				current_folder = os.path.join(dest, count / fold_capacity)
				os.mkdir(current_folder)
			open(os.path.join(current_folder, item), 'wb').write(open(abs_item, 'rb').read())

if __name__ == '__main__':
	copy_file('weiquan', 'temp')
