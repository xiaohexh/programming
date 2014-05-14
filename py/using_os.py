#!/usr/bin/python
# Filename: using_os.py

import os
import linecache

# get os name, window:nt, Unix/Linux:posix
print 'OS name:', os.name

# get current work dir
print 'current work directory:', os.getcwd()

# list file and file folder under some directory given
fileList = os.listdir('.')  # list file and file folder under current directory
print 'file & dir under current directory:'
print fileList

# create a file and write something into it
fileName = 'test_file.data'
testCon = 'Hello'
fd = file(fileName, 'w')
fd.write(testCon)
fd.close()

testFilePath = os.getcwd() + os.sep + fileName
print 'full path of test file:', testFilePath

# check if file exist, read it and delete it if exist
if os.path.exists(testFilePath):

	pathList = os.path.split(testFilePath)  # get pre-path and file name
	testFileName = pathList[1]  # get file name

	lines = linecache.getlines(testFileName) # read file content using linecache module
	print 'contents in %s' % testFilePath
	for line in lines:
		print line

	print 'remove file:%s' % testFilePath
	os.remove(testFilePath)	# remove file
else:
	print '%s is not exist.' % testFilePath
