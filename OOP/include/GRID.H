#ifndef GRID_H_
#define GRID_H_

//#include "SHIP.H"
#include <utility>

class Ship;

using namespace std;

using coords = pair<int, int> ;


class Place {
public:
	char Flag;
	Ship * ShipHere;
	Place();
};


class Grid {
private:
	Place Places[10][10];
	void Hit(Ship * ship, coords);
	void Miss(coords);

public:
	Grid();
	bool isAvaliable(coords);
	void setPlace(Ship* ship, coords);
	void HitOrMiss(coords);
	bool wasShot(coords);
	void Print();
	char get_Flag(coords);
};

#endif // !GRID_H_
