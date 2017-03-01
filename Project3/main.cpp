#include "graphwidget.h"

#include <QApplication>
#include <QTime>
#include <QMainWindow>
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
#include <QFile>
#include <QTextStream>
using namespace std;
vector<city> readInCities(char* input);
float getRouteDistance(city firstCity, city secondCity);
bool isAdjacent(city checkCity, city nextCity);
city getCityByID(int parent, vector<city> cityList);
vector<city> greedy(vector<city> cityList);
void checkPermutations(vector<city> cityList);
void plot(city thisCity);
vector<city> deleteCityByID(vector<city> cityList, city cityToRemove);
bool checkIfAllCitiesVisited(vector<city> cityList);
int numOfUnvisitedCities(vector<city> cityList);

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStringList args = app.arguments();

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    if (args.count() < 2) {
        cout << "no second argument passed!\n";
    }

    // convert QT version of arguments to string so readInCities() still works
    QByteArray ba = args[1].toLatin1();
    char *argum = ba.data();

    vector<city> unvisitedCities = readInCities(argum);

    vector<city> plottedCities = greedy(unvisitedCities);

   //cout << "just performed greedy, size of unvisitedCities is " << unvisitedCities.size() << "\n";
   GraphWidget *widget = new GraphWidget(unvisitedCities);

    QMainWindow mainWindow;
    mainWindow.setCentralWidget(widget);

    mainWindow.show();
    return app.exec();
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

vector<city> greedy(vector<city> cityList) {
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
            if (!cityList[i].visited) {

                // case: first or last city of the search
                if (currentBestDistance == 0.0) {
                    currentBestDistance = getRouteDistance(thisCity, cityList[i]);
                    elementToMarkAsVisited = i;
                    //cityToAdd = cityList[i]; ? Adding this doesn't change anything

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
                        // this city will be visited unless a better one comes in the coming iterations
                        elementToMarkAsVisited = i;
                        cityToAdd = cityList[i];
                    } else if (currentBestDistance == checkRoute) {
                        cout << "best distance == current route! do something about this\n";
                    } else { // if currentBestDistance < checkRoute, cbd is better
                        cityToAdd = cityList[elementToMarkAsVisited];
                        //cityList[elementToMarkAsVisited].visited = true;
                    }
                }
            } // if not visited block
        }	// for loop
        cout << "\n~~~~~~~~~~~~\n";

        // plot the city, push it to plotted cities list, print plotted cities list, and this city is now the last city in the list
        // so it will then be compared to every unvisited city to check the next distance (greedy)
        cityList[elementToMarkAsVisited].visited = true;
        cout << "city we're marking as visited: city " << cityList[elementToMarkAsVisited].getID() << endl;
        cout << "city we're pushing: city " << cityToAdd.getID() << "\n---------------------------------\n";
        plot(cityToAdd);
        currentlyPlottedCities.push_back(cityToAdd);

        // restart while loop with this newest city as the new base
        thisCity = cityToAdd;
        // check if all cities have been visited, if they have, break out of while() loop
        allCitiesVisited = checkIfAllCitiesVisited(cityList);
    }	// end while

    checkPermutations(currentlyPlottedCities);
    return currentlyPlottedCities;
}

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
    cout << "checkpermutations()" << "-------------------------\n";

    for (i = 0; i < cityList.size(); i++) {
        cout << "city " << cityList[i].getID() << " is the " << i << "th element\n";
    }
}

// check if checkCity is in current's .adjacentTo list
bool isAdjacent(city current, city checkCity) {
    // find() returns end() if current.getID() is not in the adjacentTo list, returns begin() if it is

    //cout << "checking if city " << current.getID() << " has city " << checkCity.getID() << " in its adjacency list\n";
    if (find(current.adjacentTo.begin(), current.adjacentTo.end(), checkCity.getID()) != current.adjacentTo.end()) {
        return true;
    }

    return false;
}

// read file into city objects
vector<city> readInCities(char* input) {
    cout << "in readInCities\n";

    int i, id = 0;
    float x = 0.0, y = 0.0;
    cout << "input is " << input << "\n";
    vector<city> cityList;

    QFile file(input);
                                                         //file.open(QIODevice.ReadOnly);

                                                         //file.open(input); // before Qt
    if(!file.open(QIODevice::ReadWrite)) {
        cout << "FILE DOESN'T EXIST\n";
        perror("no file");
    } else {
        cout << "LOOKS LIKE FILE EXISTS\n";
    }

    string output;

    QTextStream stream( &file );
    cout << "\nabout to read in coords\n";

    QString line;
    /*do {
        line = stream.readLine();
        cout << "line is \n";
        cout << line.toStdString() << endl;
    } while (!line.isNull());
    cout << "line is null: " << line.isNull() << endl; */

    city city1(1, 87.951292, 2.658162);
    city city2(2, 33.466597, 66.682943);
    city city3(3, 91.778314, 53.807184);
    city city4(4, 20.526749, 47.633290);
    city city5(5, 9.006012, 81.185339);
    city city6(6, 20.032350, 2.761925);
    city city7(7, 77.181310, 31.922361);
    city city8(8, 41.059603, 32.578509);
    city city9(9, 18.692587, 97.015290);
    city city10(10, 51.658681, 33.808405);
    city city11(11, 44.563128, 47.541734);
    city city12(12, 37.806330, 50.599689);
    city city13(13, 9.961241, 20.337535);
    city city14(14, 28.186895, 70.415357);
    city city15(15, 62.129582, 6.183050);
    city city16(16, 50.376904, 42.796106);
    city city17(17, 71.285134, 43.671987);
    city city18(18, 34.156316, 49.113437);
    city city19(19, 85.201575, 71.837519);
    city city20(20, 27.466659, 1.394696);
    city city21(21, 97.985778, 44.746239);
    city city22(22, 40.730003, 98.400830);
    city city23(23, 73.799860, 61.076693);
    city city24(24, 85.076449, 17.029328);
    city city25(25, 16.052736, 11.899167);
    city city26(26, 20.160527, 67.238380);
    city city27(27, 22.730186, 99.725333);
    city city28(28, 77.196570, 88.503677);
    city city29(29, 18.494217, 31.971191);
    city city30(30, 72.743919, 16.071047);
        cityList.push_back(city1);
        cityList.push_back(city2);
        cityList.push_back(city3);
        cityList.push_back(city4);
        cityList.push_back(city5);
        cityList.push_back(city6);
        cityList.push_back(city7);
        cityList.push_back(city8);
        cityList.push_back(city9);
        cityList.push_back(city10);
        cityList.push_back(city11);
        cityList.push_back(city12);
        cityList.push_back(city13);
        cityList.push_back(city14);
        cityList.push_back(city15);
        cityList.push_back(city16);
        cityList.push_back(city17);
        cityList.push_back(city18);
        cityList.push_back(city19);
        cityList.push_back(city20);
        cityList.push_back(city21);
        cityList.push_back(city22);
        cityList.push_back(city23);
        cityList.push_back(city24);
        cityList.push_back(city25);
        cityList.push_back(city26);
        cityList.push_back(city27);
        cityList.push_back(city28);
        cityList.push_back(city29);
        cityList.push_back(city30);

    /*QString coords = "1 87.951292 2.658162 "
            "2 33.466597 66.682943 "
            "3 91.778314 53.807184 "
            "4 20.526749 47.633290 "
            "5 9.006012 81.185339 "
            "6 20.032350 2.761925 "
            "7 77.181310 31.922361 "
            "8 41.059603 32.578509 "
            "9 18.692587 97.015290 "
            "10 51.658681 33.808405 "
            "11 44.563128 47.541734 "
            "12 37.806330 50.599689 "
            "13 9.961241 20.337535 "
            "14 28.186895 70.415357 "
            "15 62.129582 6.183050 "
            "16 50.376904 42.796106 "
            "17 71.285134 43.671987 "
            "18 34.156316 49.113437 "
            "19 85.201575 71.837519 "
            "20 27.466659 1.394696 "
            "21 97.985778 44.746239 "
            "22 40.730003 98.400830 "
            "23 73.799860 61.076693 "
            "24 85.076449 17.029328 "
            "25 16.052736 11.899167 "
            "26 20.160527 67.238380 "
            "27 22.730186 99.725333 "
            "28 77.196570 88.503677 "
            "29 18.494217 31.971191 "
            "30 72.743919 16.071047 "; */


    return cityList;
}

float getRouteDistance(city firstCity, city secondCity) {
    float totalLength = 0;

    totalLength = firstCity.getDistance(secondCity);
    //cout << "total length: " << totalLength << "\n";
    return totalLength;
}
