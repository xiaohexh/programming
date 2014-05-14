#!/usr/bin/python
# Filename: objvar.py

class Person:
	'''Represents a person.'''
	population = 0

	def __init__(self, name, age):   # like constructor, invoke by self
		'''Initialzes the person's data.'''
		self.name = name             # public
		self.__age = age             # private domain, begin with '__'
		print 'Initializeing %s.' % self.name

		Person.population += 1

	def __del__(self):          # like destructor, invoke by self
		'''I am dying.'''
		print 'say bye to %s' % self.name

		Person.population -= 1

	def sayHi(self):
		print 'Hi, %s' % self.name

	def count(self):
		print 'Total number of persons:%d' % Person.population

def addPerson():
	p1 = Person('Chris', 32)
	p1.sayHi()
	p1.count()

addPerson()
p2 = Person('Andy', 30)
p2.count()
print 'Population:%d' % Person.population
p2.sayHi()
p2.count()
print p2.name    # legal
#print p2.__age   # illegal, __age is private
