#!/usr/bin/python
# Filename: pickling.py

# use pickle module to dump/load a whole object to/from file
#import cPickle as p   # nick name
import pickle as p

shopListFile = 'shop_list.data'

shopList = ['apple', 'mango', 'carrot']

f = file(shopListFile, 'w')
p.dump(shopList, f)
f.close()

del shopList
f = file(shopListFile)
storedList = p.load(f)
print storedList 
