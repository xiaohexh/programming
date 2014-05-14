#!/usr/bin/python
# Filename: using_file.py

poem = '''\
Programming is fun
When the work is done
if you wanna make your work also fun:
        use Python!
'''

f = file('poem.txt', 'w')   # open for 'w'riting
f.write(poem)
f.close()

f = file('poem.txt') # open for 'r'ead, 'r'ead mode is assumed by default
lines = f.readlines()
print 'line number:%d' % len(lines)
f.seek(0)
while True:
	line = f.readline()
	if len(line) == 0:
		break
	print line,
f.close()
