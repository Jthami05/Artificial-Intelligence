from Tkinter import *
from city import City
from TourManager import TourManager
from population import Population
from ga import GA
import time

class tspGA:
	
	def printToFile(self, distances):
		filename = "output.txt"
		outputFile = open(filename, "w+")
		
		for i in range(0, len(distances)):
			outputFile.write(str(distances[i]))
			outputFile.write("\n")
		
		outputFile.close()
		
		
	
	def createGui(self, winningTour, distance, popNum, genNum, finalTime):
		Map = Tk()
		canv = Canvas(Map, width=1000, height=800, bg="white")
		Map.title("Traveling Salesman -Genetic")
		Map.geometry("1000x800")
	
		for city in winningTour.tour:
			city.x *= 5
			city.y *= 5
			canv.create_oval(city.x+300, city.y+50, city.x+308, city.y+58)
			canv.create_text(city.x+305, city.y+70, text=city.id)
		
		for i in range(len(winningTour.tour)-1):
			canv.create_line(winningTour.tour[i].x+304, winningTour.tour[i].y+54, winningTour.tour[i+1].x+304, winningTour.tour[i+1].y+54)
	
		canv.create_line(winningTour.tour[len(winningTour.tour)-1].x+304, winningTour.tour[len(winningTour.tour)-1].y+54, winningTour.tour[0].x+304, winningTour.tour[0].y+54)
		distanceLabel = "total distance: " + str(distance)
		popLabel = "Population: " + str(popNum)
		genLabel = "Generations: " + str(genNum)
		timeLabel = "Time taken: " + str(finalTime)
		
		canv.create_text(700,600, text=distanceLabel)
		canv.create_text(700, 615, text=popLabel)
		canv.create_text(700, 630, text=genLabel)
		canv.create_text(700, 645, text=timeLabel)
		canv.pack()
		Map.mainloop()
	
	
	def readInCities(self):
		thisCity = City(1,2,3)
		#script, filename = argv
		filename = raw_input("Input filename here: \n> ")
		file = open(filename)
		# use this if you don't want to prompt the user for the filename:
		# file = open(filename)
		# print file.read()
		for line in file:
			readCityList = []
			if "NODE_COORD_SECTION" in line:
				readCityList = []
				for line in file:
					fields = line.strip().split()
					thisID = int(fields[0])
					thisX = float(fields[1])
					thisY = float(fields[2])
					thisCity = City(thisID, thisX, thisY)
					readCityList.append(thisCity)
		return readCityList
	
	
	def main(self):
		
		tm = TourManager()
		
		cityList = self.readInCities()
		
		for i in range(0, len(cityList)):
			tm.addCity(cityList[i])
			
		numCities = len(cityList)
		getPopSize = int(raw_input("Enter the population size... >"))
		getGenSize = int(raw_input("Enter the number of generations... >"))
		
		ti = time.clock()
		# pass true because we're initializing the population (parent generation)
		pop = Population(getPopSize, True, numCities)
		
		i = 0
		ga = GA()
		distances = []
		
		pop = ga.wiseEvolvePopulation(pop, numCities)
		for i in range(0, getGenSize):
			print "evolving generation " + str(i)
			pop = ga.wiseEvolvePopulation(pop, numCities)
			distances.append(pop.getFittest().getDistance())
			
		winningDistance = pop.getFittest().getDistance()
		finalTime = time.clock() - ti
		
		print "------------------ FINISHED ------------------"
		print "time taken: " + str(finalTime) + " seconds."
		print "final distance: " + str(winningDistance)
		self.createGui(pop.getFittest(), winningDistance, getPopSize, getGenSize, finalTime)
		
		self.printToFile(distances)
		
if __name__ == "__main__":
	tsp = tspGA()
	tsp.main()
