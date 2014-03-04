#!/bin/bash
# delete user std[01~30]

# first implementation
#for i in {01..30}
#do
#	userdel std$i
#done

# second implementation
i=1
while [ $i -le 30 ]
do
#userdel -r std$i
	if [ $i -lt 10 ]; then
		echo 0$i
	else
		echo $i
	fi
	i=`expr $i + 1`  #equal to let i++
done
