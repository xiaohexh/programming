#!/usr/bin/python

import xml.dom.minidom
dom = xml.dom.minidom.parse("book.xml")
root = dom.documentElement

for node in root.childNodes:
	if node.nodeType == node.ELEMENT_NODE:
		author = node.getElementsByTagName("author")
		for names in author:
			for name in names:
				print names.name.data
