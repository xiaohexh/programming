#!/usr/bin/python
# Filename: inherit.py

class SchoolMember:
	'''Base class SchoolMember'''
	def __init__(self, name, age):
		self.name = name
		self.age = age

	def tell(self):
		print 'I am %s, and %d years old' % (self.name, self.age)
	
class Teacher(SchoolMember):
	'''Teacher class inherit from SchoolMember'''
	def __init__(self, name, age, salary):
		SchoolMember.__init__(self, name, age)
		self.salary = salary

	def tell(self):
		SchoolMember.tell(self)
		print 'and my salary is %d' % self.salary

class Student(SchoolMember):
	'''Student class inherit from SchoolMember'''
	def __init__(self, name, age, grade):
		SchoolMember.__init__(self, name, age)
		self.grade = grade

	def tell(self):
		SchoolMember.tell(self)
		print 'and my grade is %d' % self.grade

t = Teacher('Chris', 32, 2349)
s = Student('Andy', 23, 8)

l = [t, s]
for p in l:
	p.tell()
