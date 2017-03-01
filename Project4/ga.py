from population import Population
from Tour import Tour
import random
import math

class GA:
	mutationRate = 0.03
	selectionSize = 5
	elitism = True
	
	def evolvePopulation(self, pop, numCities):
		newPopulation = Population(pop.populationSize(), False, numCities)
		elitismOffset = int(math.floor(pop.populationSize() * 0.2))
		
		# Retain the top 20% elite individuals of the population
		if (self.elitism):
			for j in range(0, elitismOffset):
				newPopulation.saveTour(j, pop.getFittest(), True) # this actually takes the 1 (!) fittest individual and copies him in several times
		#	elitismOffset = 20		
		for i in range(elitismOffset, pop.populationSize()):
			parent1 = self.getParents(pop, numCities)
			parent2 = self.getParents(pop, numCities)
			child = self.crossover(parent1, parent2, numCities)
			newPopulation.saveTour(i, child)
			
		for i in range(elitismOffset, newPopulation.populationSize()):
			self.mutate(newPopulation.getTour(i))
		return newPopulation
		
	def crossover(self, parent1, parent2, numCities):
		child = Tour(numCities)
		startPos = int(random.random() * parent1.tourSize())
		endPos = int(random.random() * parent1.tourSize())
		
		# parent 1
		for i in range(0, child.tourSize()):
			# add city to child tour from parent1 that is between startPos and endPos
			if ((startPos < endPos) and (i > startPos) and (i < endPos)):
				child.setCity(i, parent1.getCity(i))
			elif (startPos > endPos):
				if not((i < startPos) and (i > endPos)):
					child.setCity(i, parent1.getCity(i))
					
		# parent 2
		for i in range(0, parent2.tourSize()):
			if not(child.containsCity(parent2.getCity(i))):
				for j in range(0, child.tourSize()):
					try:
						if (child.getCity(j) == None):
							child.setCity(j, parent2.getCity(i))
							break
					except IndexError:
						a = raw_input("IndexError in crossover mutation.")
						child.setCity(j, parent2.getCity(i))
		return child
		
	def mutate(self, tour):
		#for tourPos1 in range(0, tour.tourSize()):
		#	if (random.random() < self.mutationRate):
		#		tourPos2 = (int) ((tour.tourSize()) * random.random())
				
		for tourPos1 in range(0, tour.tourSize()):
			if (random.random() < self.mutationRate):
				tourPos2 = (int) (tour.tourSize() * random.random())
					
				# swap mutation ---------------
				city1 = tour.getCity(tourPos1)
				city2 = tour.getCity(tourPos2)
				tour.setCity(tourPos2, city1)
				tour.setCity(tourPos1, city2)
				
				# inversion mutation ---------
				#city1 = tour.getCity(tourPos1)
				#city2 = tour.getCity(tourPos2)
				
				#if (tourPos2 < tourPos1):
				#	minim = tourPos2
				#	maxim = tourPos1
				#else:
				#	minim = tourPos1
				#	maxim = tourPos2
				
				#sublist=tour.tour[minim:maxim]
   				#sublist.reverse()
  				#tour.tour[minim:maxim]=sublist
				
	def getParents(self, pop, numCities):
		parentPop = Population(self.selectionSize, False, numCities)
		for i in range(0, self.selectionSize):
			randomID = int( (random.random() * pop.populationSize()) )
			parentPop.saveTour(i, pop.getTour(randomID))
			
		fittest = parentPop.getFittest()
		return fittest
		
		
### swap mutation:
#tour.setCity(tourPos2, city1)
#tour.setCity(tourPos1, city2)
#for tourPos1 in range(0, tour.tourSize()):
#	if (random.random() < self.mutationRate):
#	tourPos2 = (int) (tour.tourSize() * random.random())
#	city1 = tour.getCity(tourPos1)
#	city2 = tour.getCity(tourPos2)
#	tour.setCity(tourPos2, city1)
#	tour.setCity(tourPos1, city2)
