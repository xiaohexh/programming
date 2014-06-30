#!/usr/bin/python

# base class Bird
class Bird():

	def haveFeather(self):
		return self._have_feather

	def fly(self):
		print 'I am flying'

	def move(self, dx, dy):
		self._position[0] += dx
		self._position[1] += dy
		return self._position

	_have_feather = True
	_position = [0, 0]

# sub-class inherit from Bird
class Chicken(Bird):

	def __init__(self, name = 'Chicken'):
		self._name = name

	def name(self):
		return self._name


if __name__ == '__main__':
	bird = Bird()
	if bird.haveFeather():
		bird.fly()
	position = bird.move(5, 9)
	print position
	position = bird.move(15, 20)
	print position

	chicken = Chicken()
	print chicken.name()
	if chicken.haveFeather():
		pos = chicken.move(12, 23)
		print pos
