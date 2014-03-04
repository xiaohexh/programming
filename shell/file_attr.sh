#!/bin/bash

create_dirs()
{
	echo $1
	for index in {1..50}
	do
		mkdir user$index
		chmod 0754 user$index
		index=`expr $index + 1`
	done
}

echo "***************"
if [ ! -d "/userdata" ]; then
	mkdir /userdata
	cd /userdata
fi

echo "=========="
msg='In create_dirs function'
create_dirs "$msg"
