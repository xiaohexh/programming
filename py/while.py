#!/usr/bin/python
# Filename: while.py

number = 23
running = True

while running:
	guess = int(raw_input('Enter an integer:'))

	if guess == number:
		print 'You got it'
		running = False
	elif guess < number:
		print 'Small'
	else:
		print 'Larger'
else:  # while. else sentence is optional
	print 'Quit while loop'

print 'Done'
