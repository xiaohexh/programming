#!/usr/bin/python
# Filename: if.py

number = 23
guess = int(raw_input('Enter an integer:'))

if guess == number:
	print 'Congratulations'
	# You got it
elif guess < number:
	print 'Smaller than', number
else:
	print 'Larger than', number

print 'Done'
# This last statement always executed
