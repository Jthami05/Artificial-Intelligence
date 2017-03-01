import math

class City:

	id = 5
	x = 1.2
	y = 1.2
	
	# using id = -2 for children cities unless necessary
	# defaulting x and y coordinates to a random location to account for children cities, otherwise they're given
	def __init__(self, idin = -2, xin = -3, yin = -4):
		self.id = idin
		self.x = xin
		self.y = yin
		self.visited = 0
		
	def __str__(self):
		return str(self.id)
	
	def getX(self):
		return self.x
	
	def getY(self):
		return self.y
		
	def getID(self):
		return self.id
		
#	def __getitem(self):
#		return {x: self.x, y, self.y}
		
	def distanceTo(self, city):
		#print "distanceTo: type of city is: "
		#print city.__class__
		
		x2 = city.x
		y2 = city.y
	
		x2 -= self.x
		y2 -= self.y
		
		x2 *= x2
		y2 *= y2
		
		return math.sqrt(x2 + y2)

# boston = City(1,2.5,3.5)
