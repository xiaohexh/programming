#!/usr/bin/python

sentence = raw_input('enter one sentence:')
for char in sentence:
	print char,

print '\n', 20 * '='

i = 0
length = len(sentence)
while i < length:
	print sentence[i],
	i += 1
