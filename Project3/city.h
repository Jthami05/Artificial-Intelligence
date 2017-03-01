#ifndef CITY_H
#define CITY_H

#include <fstream>
#include <vector>
#include <deque>

using namespace std;

class city {
    public:
        city(int idin, float xin, float yin);
        void setX(float xin);
        void setY(float yin);
        float getDistance(city cityPtr);
        float getX();
        float getY();
        int getID();
        int getPosition();
        bool isVisited();
        city getParent(int id);
        int parent;
        float distance;
        vector<int> adjacentTo;
        bool visited;
        float x;
        float y;
        int id;

    /*private:
        float x;
        float y;
        int id;*/
};

#endif // CITY_H
