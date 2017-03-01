from city import City

class TourManager:
	
	destinationCities = []
	
	def addCity(self, city):
		self.destinationCities.append(city)
	
	def getCity(self, index):
		return self.destinationCities[index] # necessary to cast?
	
	def numberOfCities(self):
		return len(self.destinationCities)
	
	
