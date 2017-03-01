from Tkinter import *
from population import Population
from Tour import Tour
import random
import copy
import math

class GA:
	mutationRate = 0.03
	selectionSize = 5
		
	def evolvePopulation(self, pop, numCities, elitism = True):
		newPopulation = Population(pop.populationSize(), False, numCities)
		elitismOffset = 0
		#elitism = True
		
		#####################################
		# run up till 20% of the population #
		#####################################
		if (elitism):
			elitismOffset = int(math.floor(pop.populationSize() * 0.35))
			#print "elitismOffset is " + str(elitismOffset)
			for j in range(0, elitismOffset):
				newPopulation.saveTour(j, pop.getFittest()) # this actually takes the 1 (!) fittest individual and copies him in several times
				
		#####################################
		#   crossover (breed) and mutate    #
		#####################################
		for i in range(elitismOffset, pop.populationSize()):
			parent1 = self.getParents(pop, numCities)
			parent2 = self.getParents(pop, numCities)
			child = self.crossover(parent1, parent2, numCities)
			newPopulation.saveTour(i, child)
			
		for i in range(elitismOffset, newPopulation.populationSize()):
			self.mutate(newPopulation.getTour(i))
			
		return newPopulation
	
	# check if tours are marked so we can see if different tours are being saved to wiseCrowd
	def checkMarkedCities(self, pop):
		for i in range(0, pop.populationSize()):
			print "Tour " + str(i) + " with distance " + str(pop.getTour(i).getDistance()) + " marked? " + str(pop.getTour(i).isVisited())
	
	############################################
	# Evolve w/20% wise crowd, itself evolved  #
	# with 10% elite crowd					   #
	############################################
	def wiseEvolvePopulation(self, pop, numCities):
	
		newPopulation = Population(pop.populationSize(), False, numCities)
		elitismOffset = int(math.floor(pop.populationSize() * 0.2))
		
		for i in range(0, pop.populationSize()):
			pop.markTour(i, False)
		
		# Retain the top 20% elite individuals of the population
		wiseCrowd = Population(elitismOffset, False, numCities)
		
		############################################
		# Creating the Wise Crowd:				   #
		# get fittest from pop, mark it as visited #
		# and get the next fittest. Wise Crowd is  #
		# 20% of population                        #
		############################################
		
		for j in range(0, elitismOffset):
			wiseCrowd.saveTour(j, pop.getFittest())
			#self.checkMarkedCities(pop)
		
		# after adding tours to wiseCrowd, we must evolve them:
		self.wisdomOfCrowds(wiseCrowd, numCities)
		
		# save evolved wise crowd members in the new population
		for i in range(0, elitismOffset):
			newPopulation.saveTour(i, wiseCrowd.getTour(i))
			
		#####################################
		#   crossover (breed) and mutate    #
		#####################################
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
	#	pass
		for tourPos1 in range(0, tour.tourSize()):
			if (random.random() < self.mutationRate):
				tourPos2 = (int) (tour.tourSize() * random.random())
					
				# swap mutation ---------------
				#city1 = tour.getCity(tourPos1)
				#city2 = tour.getCity(tourPos2)
				#tour.setCity(tourPos2, city1)
				#tour.setCity(tourPos1, city2)
				
				# inversion mutation ---------
				city1 = tour.getCity(tourPos1)
				city2 = tour.getCity(tourPos2)
				
				if (tourPos2 < tourPos1):
					minim = tourPos2
					maxim = tourPos1
				else:
					minim = tourPos1
					maxim = tourPos2
				
				sublist=tour.tour[minim:maxim]
   				sublist.reverse()
  				tour.tour[minim:maxim] = sublist
				
	# gets 5 random tours from the original population and finds the fittest
	def getParents(self, pop, numCities):
		parentPop = Population(self.selectionSize, False, numCities)
		for i in range(0, self.selectionSize):
			randomID = int( (random.random() * pop.populationSize()) )
			parentPop.saveTour(i, pop.getTour(randomID))
			
		fittest = parentPop.getFittest()
		return fittest
		
	# evolve this wise crowd several times
	def wisdomOfCrowds(self, wiseCrowd, numCities):
		for i in range(0, 10):
			#print "evolving wise crowd, generation: " + str(i)
			wiseCrowd = self.evolvePopulation(wiseCrowd, numCities, True)
			# Do Mutate = 1927, 1859, 1880
			# Don't Mutate = 1903, 1872, 1916
			# Result: 11 point difference -> irrelevant
			
			# WOC with elitism: 
			# WOC without elitism: 

# our population size is always 50 because we create a new population of size 50 every generation and it is populated with copies of the top
# solution (10% of the population) number of times. Then, we perform crossover to create a child for the rest of the population and mutate.
