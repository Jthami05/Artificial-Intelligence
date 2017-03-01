#include "city.h"
#include "math.h"
#include <iostream>
#include <fstream>

using namespace std;

city::city (int idin, float xin, float yin) {
	id = idin;
	x = xin;
	y = yin;
}

/* city::city (city & source) {
	id = source.id;
	x = source.x;
	y = source.y;
	visited = source.visited;
} */

// destructor
//city::~city() {}


// x2 is x-distance from 2nd to 1st city
// x comes from [i]th element, x2 is [i-1]
float city::getDistance(city cityPtr) {
	 
	float x2 = cityPtr.getX();
    float y2 = cityPtr.getY();
    //cout<<"11111111111111 x2 and x are: "<<x2<<", "<<x<<"\n";
	x2 -= x;
    y2 -= y;
    
    x2 *= x2;
    y2 *= y2;
  /*  cout<<"x is "<<x<<"\n--------\n";
    cout<<"y is "<<y<<"\n--------\n";    
	cout<<"x2 is "<<x2<<"\n--------\n";
	cout<<"y2 is "<<y2<<"\n--------\n";*/
    return sqrt(x2 + y2);		// TODO: remove floor() and + 0.5 ?
}

void city::setX(float xin) {
	x = xin;
}

void city::setY(float yin) {
	y = yin;
}

float city::getX()
{
    return x;
}

/*
x2 from 2nd, which is [i]
x from 1st, which is [i-1]


*/
float city::getY() 
{
    return y;
}

int city::getID()
{
    return id;
}
