#ifndef GRID_H_
#define GRID_H_

#include "SHIP.H"

class Grid {
private:
	class Place;
	Place Places[10][10];
	void Hit();
	void Mis();

public:
	Grid();
	bool isAvaliable();
	void setPlace();
	void HitOrMiss();

};

class Place {
public:
	char Flag;
	Ship* ShipHere;
	Place();
}

#endif // !GRID_H_
