from TourManager import TourManager
from random import shuffle
class Tour:
	
	# PROBLEM IS: distance == 0 when we call the mutation function and create a child tour through genetic crossover.
	# distance calculation works fine for the parent generation.
	# Are x and y coordinates being created for the children tours? Probably not and therefore there's no distance. 
	
	tm = TourManager()
	tour = []
	fitness = 0
	distance = 0
	id = 0
	marked = False
	
	# tour id = -1 for child tours, parent tours will have IDs
	
	def __init__(self, numCities, id = -1):
		if (numCities != 0):
			self.tour = [None]*numCities
			
			# initialize flag as False for wise crowd creation
			self.marked = False
		else:
			self.tour = []
		self.id = id
		
	# generating a tour, called from population.py
	def generateIndividual(self):
		for cityIndex in range(0, self.tm.numberOfCities()):
			self.setCity(cityIndex, self.tm.getCity(cityIndex))
		
		shuffle(self.tour)
	
	def isVisited(self):
		return self.marked
	
	# for solution using probability matrix
	def lastIndexOf(self, indexOfChildCity):
		# get index of last city in the tour that has the same x-value as child
		child = self.getCity(indexOfChildCity)
		for i in range(0, child.getTourSize()):
			if (self.getCity(i).getX() == child.getCity(i).getX()):
				index = i
				
		return index
		
	
	def getCity(self, tourPosition):
		return self.tour[tourPosition]
		# GETS BY INDEX, NOT BY ID
		
	# set city into tourPosition in the tour
	def setCity(self, tourPosition, city):
		self.tour[tourPosition] = city
		# self.tour.append(city)
		self.fitness = 0
		self.distance = 0.0
	
	def getFitness(self):
		if (self.fitness == 0):
			a = self.fitness = 1 / self.getDistance()
		return self.fitness
	
	def getDistance(self):
		if (self.distance == 0):
			tourDistance = 0
			#print "				tour size is " + str(self.tourSize()) + " for tour " + str(self.id)
			# appears that tourSize() being 0 makes this not happen, for the last loop
			for cityIndex in range(0, self.tourSize()):
					
				fromCity = self.getCity(cityIndex)
				if (cityIndex+1 < self.tourSize()):
					
					destinationCity = self.getCity(cityIndex+1)
					
				else:
					# end of tour, add first city to end of list
					destinationCity = self.getCity(0)
					
				################# print "from " + str(fromCity.id) + " to " + str(destinationCity.id)	
				tourDistance += fromCity.distanceTo(destinationCity) # distanceTo() equivalent to getDistance()
			self.distance = tourDistance
		return self.distance
	
	def tourSize(self):
		return len(self.tour) # doesn't work anymore since we have a full array of None values
	
	def containsCity(self, city):
		
		if city in self.tour:
			return True
		else:
			return False
	
	def toString(self):
		geneString = "|"
		for i in range(0, self.tourSize()):
			geneString += str(self.getCity(i)) + "|"
		return geneString
