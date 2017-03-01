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
		
	private:
		float x;
		float y;
		int id;
		bool visited;
};
