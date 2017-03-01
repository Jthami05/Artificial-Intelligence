from city import City
import operator
from Tkinter import *
from datetime import datetime
import time
from sys import argv

#tStart = datetime.now()

def main():

	boston = City(1,2.2,3.2)
	cityList = readInCities()
	greedy(cityList)
	
def createGui(plottedCities, distance):
	Map = Tk()
	canv = Canvas(Map, width=1000, height=800, bg="white")
	Map.title("Traveling Salesman -Greedy")
	Map.geometry("1000x800")
	
	#canv.create_text(500,400, text="500x400")
	#canv.create_text(500,300, text="500x300")
	
	for city in plottedCities:
		city.x *= 5
		city.y *= 5
		canv.create_oval(city.x+300, city.y+50, city.x+308, city.y+58)
		canv.create_text(city.x+305, city.y+70, text=city.id)
		
	for i in range(len(plottedCities)-1):
		canv.create_line(plottedCities[i].x+304, plottedCities[i].y+54, plottedCities[i+1].x+304, plottedCities[i+1].y+54)
	
	canv.create_line(plottedCities[len(plottedCities)-1].x+304, plottedCities[len(plottedCities)-1].y+54, plottedCities[0].x+304, plottedCities[0].y+54)
	distanceLabel = "total distance: " + str(distance)
	startLabel = "Starting city: city 1"
	canv.create_text(700,600, text=distanceLabel)
	canv.create_text(700, 650, text=startLabel)
	canv.pack()
	a = raw_input("Press enter to exit...")
	
def readInCities():
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
				#print "finished: id=" + thisCity.id + ", x=" + thisCity.x + ", y=" + thisCity.y

	return readCityList
	
def getRouteDistance(firstCity, secondCity):
	totalLength = 0.0
	
	totalLength = firstCity.getDistance(secondCity)
	return totalLength
	
def numOfUnvisitedCities(cityList):
	i = 0
	for city in cityList:
		if (not city.visited):
			i += 1
	return i

def checkPermutations(cityList):
	for city in cityList:
		print "city " + str(city.id)

def checkIfAllCitiesVisited(cityList):
	for city in cityList:
		if (not city.visited):
			return False
			
	return True

def greedy(cityList):
	startTime = time.time()
	distance = 0.0
	elementToMark = 0
	checkRoute = 0.0
	plottedCities = []
	allCitiesVisited = False
	cityToAdd = City(0,0.0,0.0)
	# initialize cities as not visited
	for city in cityList:
		city.visited = False
		
	# plot first city
	cityList[0].visited = True
	thisCity = cityList[0]
	plottedCities.append(cityList[0])
	
	while (not allCitiesVisited):
		currentBestDistance = 0.0
		
		for city in cityList:
			if (not city.visited):
				
				if (currentBestDistance == 0.0):
					currentBestDistance = getRouteDistance(thisCity, city)
					elementToMark = city
				
				# last city
					if (numOfUnvisitedCities(cityList) == 1):
						city.visited = True
						cityToAdd = city # TODO: both of these unecessary
						elementToMark = city
						print "last city: city " + str(city.id) + " added!"
				else:
					checkRoute = getRouteDistance(thisCity, city)
					
					# if current route is better, it's now the best route
					if (currentBestDistance > checkRoute):
						currentBestDistance = checkRoute
						elementToMark = city
						cityToAdd = city
						
					elif(currentBestDistance == checkRoute):
						# do the same thing as if currentBestDistance < checkRoute
						pass
						
					# if currentBestDistance is better, it's a candidate for the actual best distance
					else:
						cityToAdd = elementToMark
						
		elementToMark.visited = True
		plottedCities.append(cityToAdd)
		
		distance += getRouteDistance(thisCity, cityToAdd)
		thisCity = cityToAdd
		allCitiesVisited = checkIfAllCitiesVisited(cityList)
		
	distance += getRouteDistance(cityList[0], cityList[len(cityList)-1])
	checkPermutations(plottedCities)
	elapsedTime = time.time() - startTime
	print str(elapsedTime) + " seconds"
	print "total distance: " + str(distance)
	
	createGui(plottedCities, distance)
main()

# fixed local variable scope problem by initializing thisCity = City(1,2,3) at beginning of function

