#!/usr/bin/python
# Filename: using_dict.py

ab = {
	'chris' : 23,
	'andy' : 45,
	'hel' : 32
}

for key in ab:
	print key, ab[key]

if 'chris' in ab:
	print 'chris user is in dictinay'

if ab.has_key('hel'):
	print 'ab has key \'hel\''
	print 'hel:', ab['hel']
	print 'update key \'hel\' value as 33'
	ab['hel'] = 33
	print ab['hel']

print '=' * 20
for name in ab.keys():
	if ab[name] <= 40 and ab[name] >= 30:
		print 'delete this item %s:%d' % (name, ab[name])
		del ab[name]
		print 'after delete item, dic:', ab

