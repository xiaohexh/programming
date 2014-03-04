#!/bin/bash

if test $# -eq 0; then
	echo "Pls specify a file!"
else
	gzip $1   # compress file
fi

mv $1.gz $HOME/dustbin
echo "File $1 is deleted"

a=18
Name="Chris"
b=$a
echo $b, $Name
a=`expr $a + 1`
echo $a

echo "Input one directory:"
read dir
ls $dir

echo "Summary"
a=10
b=12
echo `expr $a + $b`

echo "string compare"
echo "input the first string"
read str1
echo "input the second string"
read str2
if [ $str1 = $str2 ]; then
	echo "string $str1 and $str2 is equal"
else
	echo "string $str1 and $str2 is different"
fi

if [ -n $str1 ]; then
	echo "length of string $str1 is not zero"
else
	echo "length of string $str1 is zero"
fi

if [ -z $str2 ]; then
	echo "string $str2 is null"
else
	echo "string $str2 is not null"
fi

a=20
b=31
if [ $a -eq $b ]; then
	echo "$a = $b"
elif [ $a -gt $b ]; then
	echo "$a > $b"
else
	echo "$a < $b"
fi

str1=""
str2="a"
if [ $str1 -a $str2 ]; then
	echo "$str1 and $str2 is not empty"
else
	echo "$str1 or $str2 is empty"
fi

age=24
name='Chris'
if [ $age -eq 24 -a $name = 'Chris' ]; then
	echo 'OK'
else
	echo 'Not_OK'
fi

if [ -f "move_file.sh" ]; then
	echo "move_file.sh is regular file"
fi

if [ -d '.' ]; then
	echo "Current directory is directory"
fi

if [ -x 'move_file.sh' ]; then
	echo "move_file.sh file is executable"
fi

if [ -w "move_file.sh" ]; then
	echo "move_file.sh is writable"
fi

if [ -r "move_file.sh" ]; then
	echo "move_file.sh is readable"
fi

if [ -L "move_file.sh" ]; then
	echo "move_file.sh is link file"
else
	echo "move_file.sh is non-link file"
fi

if [ -s "move_file.sh" ]; then
	echo "length of move_file.sh is greater than zero"
else
	echo "length of move_file.sh is zero"
fi

echo "Please enter the directory name or file name"
read DORF
if [ -d $DORF ]; then
	ls $DORF
else
	echo "input error"
fi

for i in a,b,c,e,I 2,4,6,8
do
	echo $i
done

for file in '.'
do
	echo $file
done

echo "sum 1 to 100"
total=0
i=1
while [ $i -le 100 ]
do
	total=`expr $total + $i`
	i=`expr $i + 1`
done
echo $total

total=0
for ((j=2; j <= 10; j++));
do
	total=`expr $total + $j`
done
echo $total

for ((num=1; num <= 100; ++num));
do
	if (($num % 2 == 0)); then
		echo -e "$num,\c"
	fi
done
echo

a=0
case $a in
'a' | 0)
echo "zero";;
*)
echo "all"
esac

case $USER in
'root')
	echo "you're root";;
'admin')
	echo "you're admin";;
*)
	echo "all"
esac

echo "==================================="
echo "Function exercise"
add()
{
	a=$1
	b=$2
	z=`expr $a + $b`
	echo "Sum of $a and $b is $z"
}

add 2 3
