#!/usr/bin/python
# Filename: object_param.py

class Student:
	'''class student for operate on student information'''
	# python not support ctor overload, so if you want create default ctor, 
	# give default value to parameter
	def __init__(self, name = '', age = -1):
		self.name = name
		self.age = age

	def setName(self, name):
		self.name = name

	def setAge(self, age):
		self.age = age

	def getName(self):
		return self.name

	def getAge(self):
		return self.age

def printStudentInfo(index, student):  # pass object parameter to function
	print 'No.%d student information:' % index
	print 'Name:%s\tAge:%d' % (student.getName(), student.getAge())

if __name__ == '__main__':
	obj1 = Student('Chris', 34);
	obj2 = Student();
	obj3 = Student('Andy', 23);
	stuList = [obj1, obj2, obj3]

	index = 1
	for student in stuList:
		printStudentInfo(index, student)
		index += 1
