#!/bin/bash
echo "Mr.$USER, Today is:"
echo `date`
echo "Wish you a lucky day!"


echo 'program name:' $0
echo 'First parameter:' $1

echo 'command path:' $0
echo 'number of parameters:' $#
echo 'result status of last command:' $?
echo 'string including all parameter:' $*
