from Tour import Tour
class Population:
	# passing populationSize won't change the actual population size, b/c we use populationSize() which gets the length of the tour.
	def __init__(self, populationSize, initialize, numCities):
		
		self.tours = []
		
		for i in range(0, populationSize):
			self.tours.append(None)#*populationSize
		if (initialize == True):
			
			for i in range(0, populationSize):
				#print "generating tour " + str(i) + "..."
				newTour = Tour(numCities, i) # pass i as id of this tour
				newTour.generateIndividual()
				self.saveTour(i, newTour)
	
	def saveTour(self, index, tour, elite = False):
		#self.tours.append(tour)
		self.tours[index] = tour
	
	def getTour(self, index):
		return self.tours[index]
	
	def getFittest(self):
		fittest = self.tours[0]
		#print fittest.__class__
		for i in range(1, self.populationSize()):	# this uses index of 1, if there's an indexing error it could be this
			if (fittest.getFitness() <= self.getTour(i).getFitness()):
				fittest = self.getTour(i)
		return fittest
	
	def populationSize(self):
		return len(self.tours)
