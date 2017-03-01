#include <typeinfo>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <stdbool.h>
#include <fstream>
#include <time.h>
#include <ostream>
#include <istream>
#include "city.h"
using namespace std; 
vector<city> readInCities(char* input);
float getRouteDistance(city firstCity, city secondCity);
bool isAdjacent(city checkCity, city nextCity);
city getCityByID(int parent, vector<city> cityList);
void greedy(vector<city> cityList);
void checkPermutations(vector<city> cityList);
void plot(city thisCity);
vector<city> deleteCityByID(vector<city> cityList, city cityToRemove);
bool checkIfAllCitiesVisited(vector<city> cityList);
int numOfUnvisitedCities(vector<city> cityList);

int main(int argc, char** argv) {
	
	vector<city> unvisitedCities = readInCities(argv[1]);
	city firstCity = unvisitedCities[0];
	float bestDistance = 0.0;
	vector<float> totalDistance;
	//clock_t tStart = clock();
	
	greedy(unvisitedCities);
	
	return 0;
}
int numOfUnvisitedCities(vector<city> cityList) {
	int i;
	int num = 0;
	
	for (i = 0; i < cityList.size(); i++) {
		if (!cityList[i].visited) {
			num++;
		}
	}
	
	return num;
}

void greedy(vector<city> cityList) {
	int i;
	int elementToMarkAsVisited = 999;
	
	float checkRoute = 0.0;
	float currentBestDistance = 0.0;
	vector<city> currentlyPlottedCities;
	bool allCitiesVisited = false;
	
	// plot the first city
	city thisCity = cityList[0];
	plot(thisCity);
	
	for (i = 0; i < cityList.size(); i++) {
		cityList[i].visited = false;
	}
	
	cityList[0].visited = true;
	currentlyPlottedCities.push_back(cityList[0]);
	
	city cityToAdd(0,0,0);
	
	while (!allCitiesVisited) {
		currentBestDistance = 0.0;
		for (i = 0; i < cityList.size(); i++) {
		cout << "---------------------\ni=" << i ;
		cout << ", city " << cityList[i].getID() << " visited: " << cityList[i].visited << endl;
			if (!cityList[i].visited) {
			
				// case: first or last city of the search
				if (currentBestDistance == 0.0) {
					cout << "distance between base city (" << thisCity.getID() << ") and cityList[i] (" << cityList[i].getID() << ")";
					currentBestDistance = getRouteDistance(thisCity, cityList[i]);
					cout << " is " << currentBestDistance << endl;
					elementToMarkAsVisited = i;
					// cityToAdd = cityList[i] ? Should I do this? TODO
					
					// last city, go ahead and add
					if (numOfUnvisitedCities(cityList) == 1) {
						cityList[i].visited = true;
						cityToAdd = cityList[i];
						elementToMarkAsVisited = i;
						cout << "last city: id " << cityList[i].getID() << " added!\n";
					}
					
					
					
				} else {	// currentBestDistance is not 0
					// checking thisCity against cityList[i]
					// if this route is more efficient, it's our route and this may be the city to add to currentlyPlottedCities
					checkRoute = getRouteDistance(thisCity, cityList[i]);
					
					cout << "testing cbd: " << currentBestDistance << " against " << checkRoute << ".\n";
					if (currentBestDistance > checkRoute) {
					
						cout << "replacing " << currentBestDistance << " with " << checkRoute << endl;
						currentBestDistance = checkRoute;
						// this city will be added to plotted cities list, and it has been visited
						
						// TODO: error is because cityToAdd isn't being marked as visited, but we have to wait to mark cityList[i]
						// mark cityList[i] after for loop TODO
						//cityList[i].visited = true;
						elementToMarkAsVisited = i;
						cityToAdd = cityList[i];
						//cout << "city to add: city " << cityList[elementToMarkAsVisited].getID() << endl;
						//cout << "2)	city " << cityList[i].getID() << " added!\n";
						//cout << "currentBestDistance is " << currentBestDistance << " and city " << cityList[i].getID() << " may be added\n";
					
					
					
					
					} else if (currentBestDistance == checkRoute) {
						cout << "best distance == current route! do something about this\n";
						break;
					} else { // if currentBestDistance < checkRoute, cbd is better
						cityToAdd = cityList[elementToMarkAsVisited];
						//cityList[elementToMarkAsVisited].visited = true;
					}
				}
			} // if not visited block
		}	// for loop
		cout << "---\n";
		
		// plot the city, push it to plotted cities list, print plotted cities list, and this city is now the last city in the list
		// so it will then be compared to every unvisited city to check the next distance (greedy)
		cityList[elementToMarkAsVisited].visited = true;
		cout << "city we're marking as visited: city " << cityList[elementToMarkAsVisited].getID() << endl;
		cout << "city we're pushing: city " << cityToAdd.getID() << "\n---------------------------------\n";
		plot(cityToAdd);
		currentlyPlottedCities.push_back(cityToAdd);
		//checkPermutations(currentlyPlottedCities);
		
		
		
		
		// restart while loop with this newest city as the new base
		thisCity = cityToAdd;
		//cityToAdd = city(99,1,1);
		
		// check if all cities have been visited, if they have, break out of while() loop
		allCitiesVisited = checkIfAllCitiesVisited(cityList);
		cout << "all cities visited? " << allCitiesVisited << endl;
	}	// end while
	
	for (i = 0; i < cityList.size(); i++) {
		cout << "city " << cityList[i].getID() << " visited: " << cityList[i].visited << endl;
	}
	
	checkPermutations(currentlyPlottedCities);
}
// TODO: Find out if vector::erase() still works for the intermediary cities (after first city's removal) up until the end. This is probably
// the error causing cities to be repeated. Create a deleteCityByID()

bool checkIfAllCitiesVisited(vector<city> cityList) {
	int i;
	for (i = 0; i < cityList.size(); i++) {
		if (!cityList[i].visited) {
			return false;
		}
	}
	return true;
}

void plot(city thisCity) {

}

void checkPermutations(vector<city> cityList) {
	int i;
	cout << "checkpermutations(), city list size: " << cityList.size() << "-------------------------\n";
	
	for (i = 0; i < cityList.size(); i++) {
		cout << "city " << cityList[i].getID() << " is the " << i << "th element\n";
	}
}
	
// check if checkCity is in current's .adjacentTo list
bool isAdjacent(city current, city checkCity) {
	int i;
	// find() returns end() if current.getID() is not in the adjacentTo list, returns begin() if it is
	
	//cout << "checking if city " << current.getID() << " has city " << checkCity.getID() << " in its adjacency list\n";
	if (find(current.adjacentTo.begin(), current.adjacentTo.end(), checkCity.getID()) != current.adjacentTo.end()) {
		return true;
	}
	
	return false;
}

// read file into city objects
vector<city> readInCities(char* input) {
	int i, id = 0;
	float x = 0.0, y = 0.0;
	
	vector<city> cityList;  
	ifstream file;
	file.open(input);
	string output;
	
	file >> output;
	while (output != "NODE_COORD_SECTION") {
		file >> output;
	}
	
	while(file >> id) {	// while file exists, read each word into output
		file >> x;
		file >> y;
		//cout << id << "\n";
		//cout << x << "\n";
		//cout << y << "\n";
		city testCity(id, x, y);
		cityList.push_back(testCity);
	}
	file.close();
	return cityList;
}

float getRouteDistance(city firstCity, city secondCity) {
	float totalLength = 0;
	
	totalLength = firstCity.getDistance(secondCity);
	//cout << "total length: " << totalLength << "\n";
	return totalLength;
}



// this is because city 1 is naturally in element [0], now city 2 is in element [0], so erasing begin()+(i-1) will erase city i because
// we're only offset by 1 because of the erasing of the first city
// TODO: ensure no problems are related to passing by value instead of by reference
