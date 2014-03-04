#!/bin/bash

# Judge whether a file is character or block file,
# if the file is character or block file,
# then copy it to /dev directory

read -p "Input file name:" file_name

if [ -f $file_name -o -b $file_name ]; then
	echo "$file_name is file or block file" && cp $file_name /dev
else
	echo "The file is not character or block file" && date
fi

if read -t 5 -p "Enter your name:" name
then
	echo "Hello $name"
else
	echo "Your input time out"
fi
