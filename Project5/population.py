from Tour import Tour
class Population:
	# passing populationSize won't change the actual population size, b/c we use populationSize() which gets the length of the tours.
	def __init__(self, populationSize, initialize, numCities):
		
		self.tours = []
		
		for i in range(0, populationSize):
			self.tours.append(None)#*populationSizeIf anyone remembers what our consensus was on Tyler Pollitt
		if (initialize == True):
			
			for i in range(0, populationSize):
				#print "generating tour " + str(i) + "..."
				newTour = Tour(numCities, i) # pass i as id of this tour, only for parent generation
				newTour.generateIndividual()
				self.saveTour(i, newTour)
	
	def saveTour(self, index, tour):
		#self.tours.append(tour)
		self.tours[index] = tour
	
	def getTour(self, index):
		return self.tours[index]
	
	def markTour(self, index, visited):
		self.tours[index].marked = visited
		
	def getFittest(self):
	# if the first element is actually the fittest, we need to mark it so that we don't include it in wiseCrowd every time we call getFittest().
	# if another element is fittest, mark that element, and unmark the first. 
		fittest = self.tours[0]
		elementToMark = 0
		
		for i in range(1, self.populationSize()):	# this uses index of 1, if there's an indexing error it could be this
			# if the city has been visited (to include in wise crowd), don't say it's the fittest, move on
			if (fittest.getFitness() <= self.getTour(i).getFitness()) and not (self.getTour(i).isVisited()):
				fittest = self.getTour(i)
				elementToMark = i
		
		self.markTour(elementToMark, True)
		return fittest
	
	def populationSize(self):
		return len(self.tours)
