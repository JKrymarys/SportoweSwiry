#ifndef GRID_H_
#define GRID_H_

#include "SHIP.H"

typedef pair<int, int>  coords;

class Place;

class Grid {
private:
	class Place;
	Place Places[10][10];
	void Hit();
	void Mis();

public:
	Grid();
	bool isAvaliable(coords(int x,int y));
	void setPlace(Ship* ship, coords(int x, int y));
	void HitOrMiss();

};

class Place {
public:
	char Flag;
	Ship* ShipHere;
	Place();
}

#endif // !GRID_H_
