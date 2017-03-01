#include <typeinfo>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <queue>
#include <algorithm>
#include <iterator>
#include <stdbool.h>
#include <fstream>
#include <time.h>
#include <ostream>
#include <istream>
#include "city.h"
#include <stack>
using namespace std; 
vector<city> readInCities(char* input);
float bruteForce(int n, vector<city> &unvisitedCities, vector<float> &totalDistance, city firstCity, clock_t tStart);
float getRouteDistance(city firstCity, city secondCity);
vector<city> swap(vector<city> &list, city firstCity, city secondCity, int i, int n);
void bfsWeighted(vector<city> cityList, city firstCity, clock_t tStart);
void bfsUnweighted(vector<city> cityList, city firstCity, clock_t tStart);
bool isAdjacent(city checkCity, city nextCity);
void dfsUnweighted(vector<city>, city aCity, clock_t tStart);
void dfsWeighted(vector<city>, city aCity, clock_t tStart);
city getCityByID(int parent, vector<city> cityList);

int main(int argc, char** argv) {
	
	vector<city> unvisitedCities = readInCities(argv[1]);
	city firstCity = unvisitedCities[0];
	float bestDistance = 0.0;
	vector<float> totalDistance;
	clock_t tStart = clock();
	bfsWeighted(unvisitedCities, unvisitedCities.front(), tStart);
	bfsUnweighted(unvisitedCities, unvisitedCities.front(), tStart);
	
	dfsWeighted(unvisitedCities, unvisitedCities.front(), tStart);
	dfsUnweighted(unvisitedCities, unvisitedCities.front(), tStart);
	return 0;
}

void dfsWeighted(vector<city> cityList, city aCity, clock_t tStart) {
	int i;
	float totalLength;
	stack<city> S;
	stack<city> logStack;
	bool* visited = new bool[cityList.size()];
	
	cout << "------------ DEPTH FIRST SEARCH WEIGHTED ------------" << "\n";
	/*** Hardcode adjacent nodes ***/
	int arr[] = {2,3,4};
	vector<int> a (arr, arr + sizeof(arr) / sizeof(arr[0]) );
	cityList[0].adjacentTo = a;
	aCity.adjacentTo = a;
	
	int bb[] = {3};
	vector<int> b (bb, bb + sizeof(bb) / sizeof(bb[0]) );
	cityList[1].adjacentTo = b;
	
	int cc[] = {4,5};
	vector<int> c (cc, cc + sizeof(cc) / sizeof(cc[0]) );
	cityList[2].adjacentTo = c;
	
	int dd[] = {5,6,7};
	vector<int> d (dd, dd + sizeof(dd) / sizeof(dd[0]) );
	cityList[3].adjacentTo = d;
	
	int ee[] = {7,8};
	vector<int> e (ee, ee + sizeof(ee) / sizeof(ee[0]) );
	cityList[4].adjacentTo = e;
	
	int ff[] = {8};
	vector<int> f (ff, ff + sizeof(ff) / sizeof(ff[0]) );
	cityList[5].adjacentTo = f;
	
	int gg[] = {9,10};
	vector<int> g (gg, gg + sizeof(gg) / sizeof(gg[0]) );
	cityList[6].adjacentTo = g;
	
	int hh[] = {9,10,11};
	vector<int> h (hh, hh + sizeof(hh) / sizeof(hh[0]) );
	cityList[7].adjacentTo = h;
	
	int jj[] = {11};
	vector<int> j (jj, jj + sizeof(jj) / sizeof(jj[0]) );
	cityList[8].adjacentTo = j;
	cityList[9].adjacentTo = j;
	/*** Hardcoded values  ***/

	for(i = 0; i <= cityList.size(); i++) {
		visited[i] = false;
	}
	
	S.push(aCity);
	visited[aCity.getID()-1] = true;
	
	while (!S.empty()) {
	
						logStack.push(S.top());
		aCity = S.top();
		S.pop();
		
		for (i = cityList.size()-1; i >= 0; --i) {
			if (isAdjacent(aCity, cityList[i]) && !visited[i]) {
				// do distance eqn calculation here
				totalLength += getRouteDistance(aCity, cityList[i]);
				S.push(cityList[i]);
				visited[i] = true;
			}
		}
	}
	
	delete [] visited;
	
	cout << "printing in reverse order...\n";
	while (!logStack.empty()) {
		cout << "city " << logStack.top().getID() << "\n";
		logStack.pop();
	}
	cout << "Total length traveled is " << totalLength << endl;
	printf("Time taken: %fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}

void dfsUnweighted(vector<city> cityList, city aCity, clock_t tStart) {
	int i;
	float totalLength;
	stack<city> S;
	stack<city> logStack;
	bool* visited = new bool[cityList.size()];
	
	cout << "------------ DEPTH FIRST SEARCH UNWEIGHTED ------------" << "\n";
	/*** Hardcode adjacent nodes ***/
	int arr[] = {2,3,4};
	vector<int> a (arr, arr + sizeof(arr) / sizeof(arr[0]) );
	cityList[0].adjacentTo = a;
	aCity.adjacentTo = a;
	
	int bb[] = {3};
	vector<int> b (bb, bb + sizeof(bb) / sizeof(bb[0]) );
	cityList[1].adjacentTo = b;
	
	int cc[] = {4,5};
	vector<int> c (cc, cc + sizeof(cc) / sizeof(cc[0]) );
	cityList[2].adjacentTo = c;
	
	int dd[] = {5,6,7};
	vector<int> d (dd, dd + sizeof(dd) / sizeof(dd[0]) );
	cityList[3].adjacentTo = d;
	
	int ee[] = {7,8};
	vector<int> e (ee, ee + sizeof(ee) / sizeof(ee[0]) );
	cityList[4].adjacentTo = e;
	
	int ff[] = {8};
	vector<int> f (ff, ff + sizeof(ff) / sizeof(ff[0]) );
	cityList[5].adjacentTo = f;
	
	int gg[] = {9,10};
	vector<int> g (gg, gg + sizeof(gg) / sizeof(gg[0]) );
	cityList[6].adjacentTo = g;
	
	int hh[] = {9,10,11};
	vector<int> h (hh, hh + sizeof(hh) / sizeof(hh[0]) );
	cityList[7].adjacentTo = h;
	
	int jj[] = {11};
	vector<int> j (jj, jj + sizeof(jj) / sizeof(jj[0]) );
	cityList[8].adjacentTo = j;
	cityList[9].adjacentTo = j;
	/*** Hardcoded values  ***/

	for(i = 0; i <= cityList.size(); i++) {
		visited[i] = false;
	}
	
	S.push(aCity);
	visited[aCity.getID()-1] = true;
	
	while (!S.empty()) {
	//cout << "went through all cities.\n";
		logStack.push(S.top());
		aCity = S.top();
		S.pop();
		
		for (i = cityList.size()-1; i >= 0; --i) {
			if (isAdjacent(aCity, cityList[i]) && !visited[i]) {
				//cout << "pushing city " << cityList[i].getID() << "\n";
				totalLength++;
				S.push(cityList[i]);
				visited[i] = true;
			}
		}
	}
	
	delete [] visited;
	
	cout << "printing in reverse order...\n";
	while (!logStack.empty()) {
		cout << "city " << logStack.top().getID() << "\n";
		logStack.pop();
	}
	cout << "Number of traversals is " << totalLength << endl;
	printf("Time taken: %fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}

void bfsWeighted(vector<city> cityList, city firstCity, clock_t tStart) {
	int i;
	city current(0, -1, -1);
	city previous(-1, -1, -1);
	float totalLength = 0.0;
	cout << "------------ BREADTH FIRST SEARCH WEIGHTED ------------" << "\n";
	
	/*** Hardcode adjacent nodes ***/
	int arr[] = {2,3,4};
	vector<int> a (arr, arr + sizeof(arr) / sizeof(arr[0]) );
	cityList[0].adjacentTo = a;
	firstCity.adjacentTo = a;
	
	int bb[] = {3};
	vector<int> b (bb, bb + sizeof(bb) / sizeof(bb[0]) );
	cityList[1].adjacentTo = b;
	
	int cc[] = {4,5};
	vector<int> c (cc, cc + sizeof(cc) / sizeof(cc[0]) );
	cityList[2].adjacentTo = c;
	
	int dd[] = {5,6,7};
	vector<int> d (dd, dd + sizeof(dd) / sizeof(dd[0]) );
	cityList[3].adjacentTo = d;
	
	int ee[] = {7,8};
	vector<int> e (ee, ee + sizeof(ee) / sizeof(ee[0]) );
	cityList[4].adjacentTo = e;
	
	int ff[] = {8};
	vector<int> f (ff, ff + sizeof(ff) / sizeof(ff[0]) );
	cityList[5].adjacentTo = f;
	
	int gg[] = {9,10};
	vector<int> g (gg, gg + sizeof(gg) / sizeof(gg[0]) );
	cityList[6].adjacentTo = g;
	
	int hh[] = {9,10,11};
	vector<int> h (hh, hh + sizeof(hh) / sizeof(hh[0]) );
	cityList[7].adjacentTo = h;
	
	int jj[] = {11};
	vector<int> j (jj, jj + sizeof(jj) / sizeof(jj[0]) );
	cityList[8].adjacentTo = j;
	cityList[9].adjacentTo = j;
	/*** Hardcoded values  ***/
	
	
	for (i = 0; i < cityList.size(); i++) {
		cityList[i].distance = 0;
		cityList[i].parent = 0;
	}
	
	queue<city> Q;
	firstCity.distance = 0;
	Q.push(firstCity);
	
	while (!Q.empty()) {
		current = Q.front();
		Q.pop();
		
		for (i = 0; i < cityList.size() - 1; i++/* each node that's adjacent to current */) {
			//cout << "searching for adjacencies to city " << current.getID() << "...\n";
			if (isAdjacent(current, cityList[i])) {
				//cout << "city " << cityList[i].getID() << " is adjacent to city " << current.getID() << "\n";
				
				if (cityList[i].distance == 0) {
					cityList[i].distance = current.distance + 1;
					cityList[i].parent = current.getID();
					//cout << "pushing city " << cityList[i].getID() << " to the Q of our current level\n";
					Q.push(cityList[i]);
					//cout << "size of Q after pushing city " << cityList[i].getID() << ": " << Q.size() << "\n";
				}							
				
			} else { // continue looking for an adjacent city
			}
		}
		//cout << "size of Q: " << Q.size() << "\n";
	}
	
	cout << "printing in order...\n";
	while (true) {
		cout << "city " << current.getID() << "\n";
		previous = current;
		current = getCityByID(current.parent, cityList);
		//cout << "total length: " << totalLength << "\n";
		totalLength += getRouteDistance(current, previous);
		//cout << "total length: " << totalLength << "\n";
		if (current.getID() == 1) {
			cout << "city " << current.getID() << "\n";
			break;
		}
	}
	
	cout << "total distance: " << totalLength << "\n";
	printf("Time taken: %fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}

void bfsUnweighted(vector<city> cityList, city firstCity, clock_t tStart) {
	int i;
	city current(0, -1, -1);
	city previous(-1, -1, -1);
	float totalLength = 0.0;
	cout << "------------ BREADTH FIRST SEARCH UNWEIGHTED------------" << "\n";
	
	/*** Hardcode adjacent nodes ***/
	int arr[] = {2,3,4};
	vector<int> a (arr, arr + sizeof(arr) / sizeof(arr[0]) );
	cityList[0].adjacentTo = a;
	firstCity.adjacentTo = a;
	
	int bb[] = {3};
	vector<int> b (bb, bb + sizeof(bb) / sizeof(bb[0]) );
	cityList[1].adjacentTo = b;
	
	int cc[] = {4,5};
	vector<int> c (cc, cc + sizeof(cc) / sizeof(cc[0]) );
	cityList[2].adjacentTo = c;
	
	int dd[] = {5,6,7};
	vector<int> d (dd, dd + sizeof(dd) / sizeof(dd[0]) );
	cityList[3].adjacentTo = d;
	
	int ee[] = {7,8};
	vector<int> e (ee, ee + sizeof(ee) / sizeof(ee[0]) );
	cityList[4].adjacentTo = e;
	
	int ff[] = {8};
	vector<int> f (ff, ff + sizeof(ff) / sizeof(ff[0]) );
	cityList[5].adjacentTo = f;
	
	int gg[] = {9,10};
	vector<int> g (gg, gg + sizeof(gg) / sizeof(gg[0]) );
	cityList[6].adjacentTo = g;
	
	int hh[] = {9,10,11};
	vector<int> h (hh, hh + sizeof(hh) / sizeof(hh[0]) );
	cityList[7].adjacentTo = h;
	
	int jj[] = {11};
	vector<int> j (jj, jj + sizeof(jj) / sizeof(jj[0]) );
	cityList[8].adjacentTo = j;
	cityList[9].adjacentTo = j;
	/*** Hardcoded values  ***/
	
	
	for (i = 0; i < cityList.size(); i++) {
		cityList[i].distance = 0;
		cityList[i].parent = 0;
	}
	
	queue<city> Q;
	firstCity.distance = 0;
	Q.push(firstCity);
	
	while (!Q.empty()) {
		current = Q.front();
		Q.pop();
		
		for (i = 0; i < cityList.size() - 1; i++/* each node that's adjacent to current */) {
			//cout << "searching for adjacencies to city " << current.getID() << "...\n";
			if (isAdjacent(current, cityList[i])) {
				//cout << "city " << cityList[i].getID() << " is adjacent to city " << current.getID() << "\n";
				
				if (cityList[i].distance == 0) {
					cityList[i].distance = current.distance + 1;
					cityList[i].parent = current.getID();
					totalLength++;
					//cout << "pushing city " << cityList[i].getID() << " to the Q of our current level\n";
					Q.push(cityList[i]);
					//cout << "size of Q after pushing city " << cityList[i].getID() << ": " << Q.size() << "\n";
				}							
				
			} else { // continue looking for an adjacent city
			}
		}
		//cout << "size of Q: " << Q.size() << "\n";
	}
	
	cout << "printing in order...\n";
	while (true) {
		cout << "city " << current.getID() << "\n";
		previous = current;
		current = getCityByID(current.parent, cityList);
		
		if (current.getID() == 1) {
			cout << "city " << current.getID() << "\n";
			break;
		}
	}
	
	cout << "Number of traversals: " << totalLength << "\n";
	printf("Time taken: %fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}

city getCityByID(int parent, vector<city> cityList) {
	int i;
	
	for (i = 0; i < cityList.size(); i++) {
		if (parent == cityList[i].getID()) {
			return cityList[i];
		}
	}
}

// check if checkCity is in current's .adjacentTo list
bool isAdjacent(city current, city checkCity) {
	int i;
	// find() returns end() if current.getID() is not in the adjacentTo list, returns begin() if it is
	
	//cout << "checking if city " << current.getID() << " has city " << checkCity.getID() << " in its adjacency list\n";
	if ( find(current.adjacentTo.begin(), current.adjacentTo.end(), checkCity.getID()) != current.adjacentTo.end()) {
		return true;
	}
	
	//for (i = 0; i < current.
	
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
	
	//cout << "calculating distance between city " << cityList[i-1].getID() << " and city " << cityList[i].getID() << "...\n";
	totalLength = firstCity.getDistance(secondCity);
	
	//cout << "total length: " << totalLength << "\n";
	return totalLength;
}


// TODO: ensure no problems are related to passing by value instead of by reference
