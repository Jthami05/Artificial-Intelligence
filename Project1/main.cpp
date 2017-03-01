#include <typeinfo>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdbool.h>
#include <fstream>
#include <time.h>
#include <ostream>
#include <istream>
#include "city.h"
using namespace std; 
vector<city> readInCities(char* input);
float bruteForce(int n, vector<city> &unvisitedCities, vector<float> &totalDistance, city firstCity, clock_t tStart);
float getRouteDistance(vector<city> cityList, city firstCity);
vector<city> swap(vector<city> &list, city firstCity, city secondCity, int i, int n);
float calculateBestDistance(vector<float> &totalDistance);
void checkDistance(vector<float> &totalDistance);
void checkPermutations(vector<city> cityList);
//int factorial(int n);

int main(int argc, char** argv) {
	
	vector<city> unvisitedCities = readInCities(argv[1]);
	city firstCity = unvisitedCities[0];
	float bestDistance = 0.0;
	
	vector<float> totalDistance;
	
	unvisitedCities.erase(unvisitedCities.begin());
	
	//int a = factorial(unvisitedCities.size());
	//cout << "factorial is " << a << "\n";
	clock_t tStart = clock();
	bruteForce(unvisitedCities.size(), unvisitedCities, totalDistance, firstCity, tStart);
	
	bestDistance = calculateBestDistance(totalDistance);
	
	//cout << "\nBest distance is " << bestDistance << "\n";
	return 0;
}

void checkPermutations(vector<city> cityList) {
	int i;
	//cout << "checkpermutations()-------------------------\n";
	
	for (i = 0; i < cityList.size(); i++) {
		cout << "city " << cityList[i].getID() << "\n";
	}
}

/*int factorial(int n) 
{
    if (n == 0)
       return 1;
    return n * factorial(n - 1);
}*/

// find best distance from vector of distances
float calculateBestDistance(vector<float> &totalDistance) {
	int i;
	float bestDistance = 0.0;
	
	for (i = 0; i < totalDistance.size(); i++) {
		if (i == 0) {
			bestDistance = totalDistance[i];
		} else {
			if (totalDistance[i] < bestDistance) {
				bestDistance = totalDistance[i];
			}
		}
	}
	return bestDistance;
}

// read file into city objects
vector<city> readInCities(char* input) {
	int i, id = 0;
	float x = 0.0, y = 0.0;
	
	vector<city> cityList;  
	ifstream file;
	file.open(input);
	string output;

	// TODO: change this for loop so that it specifically looks for strings in NODE_COORD_SECTION

	for (i = 0; i < 20; i++) {
			file >> output;	// put this line of the file into output
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

// cityList[0] DOES contain the first city, and exists up until cityList[n-1]
float getRouteDistance(vector<city> cityList, city firstCity) {
	int i;
	float totalLength = 0;
	totalLength = firstCity.getDistance(cityList[0]);
	cout << "city " << firstCity.getID() << "\n";
	for (i = 1; i < cityList.size(); i++) {
	
		//cout << "calculating distance between city " << cityList[i-1].getID() << " and city " << cityList[i].getID() << "...\n";
		totalLength += cityList[i-1].getDistance(cityList[i]);
		//cout << "adding " << cityList[i].getID() << " to list, length is " << totalLength << "\n";
	}
	i--;
	
	//cout << "---- getting distance from city " << firstCity.getID() << " to city " << cityList[i-1].getID() << ", cityList[i] is " << cityList[i].getID() << "\n";
	totalLength += cityList[i].getDistance(firstCity);
	//cout << "after: city " << firstCity.getID() << ", length is " << totalLength << "\n";
	//cout << "total length at end of getRouteDistance() is " << totalLength << "\n"; // TODO this is an important line for info
	return totalLength;
}

void checkDistance(vector<float> &totalDistance) {
	int i;
	cout << "~~~~~~~~~checkDistance()~~~~~~~~~~~~\n";
	for (i = 0; i < totalDistance.size(); i++) {
		cout << "totalDistance in checkDistance(): " << totalDistance[i] << "\n";
	}
	cout << "size of totalDistance is " << totalDistance.size() << "\n";
	cout << "~~~~~~~~~end checkDistance()~~~~~~~~~~~\n";
}
 
// call Heap's Algorithm with n-1 cities initially! B/c first city = last city
float bruteForce(int n, vector<city> &unvisitedCities, vector<float> &totalDistance, city firstCity, clock_t tStart) {
	float totalLength = 0.0;
	vector<city> visitedCities;
	int i;
	
	if (n == 1) {
		cout << "city 1\n";
		checkPermutations(unvisitedCities);
		
		totalLength = getRouteDistance(unvisitedCities, firstCity);
		totalDistance.push_back(totalLength);
		//cout << "\n\nbruteForce(): size of totalDistance is " << totalDistance.size() << "\n";
		
		float bestDistance = calculateBestDistance(totalDistance);
		cout << "\n" << "Best distance is: " << bestDistance << "\n";
		printf("Time taken: %fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
		return 5.0;
	}
	else {
		for (i = 0; i < n-1;  i++) {
		
			bruteForce(n-1, unvisitedCities, totalDistance, firstCity, tStart);
			
			if (n % 2 == 0) {
				unvisitedCities = swap(unvisitedCities, unvisitedCities[i], unvisitedCities[n-1], i, n);
			} else {
				unvisitedCities = swap(unvisitedCities, unvisitedCities[0], unvisitedCities[n-1], 0, n);
			}
		} // end for
		bruteForce(n-1, unvisitedCities, totalDistance, firstCity, tStart);
	}
}

// pass in cityList, index of a city, index of the other city, swap them inside the list.

vector<city> swap(vector<city> &list, city firstCity, city secondCity, int i, int n) {
	city tempCity = firstCity;
	list[i] = secondCity;
	list[n-1] = tempCity;
	return list;
}

//cout << "n=" << n << ", swapping place " << i << " (ID " << unvisitedCities[i].getID() << ") and place " << n-1 << " (ID " << unvisitedCities[n-1].getID() << ")\n";

//cout << "\nn=" << n << ", else swapping place " << 0 << " (ID " << unvisitedCities[0].getID() << ") and place " << n-1 << " (ID " << unvisitedCities[n-1].getID() << ")\n";
