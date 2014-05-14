#!/usr/bin/python
# Filename: using_list.py

shop_list = ['apple', 'watermelon', 'telephone', 'shoe']

print 'shopping list:'
print shop_list

print 'I have', len(shop_list), 'items to buy'

print "add 'book' to shop list"
shop_list.append('book')
print shop_list

print 'sort list:'
shop_list.sort() 
print shop_list 

print shop_list[0],'I have buy, and delete from shop list'
del shop_list[0]
print shop_list
