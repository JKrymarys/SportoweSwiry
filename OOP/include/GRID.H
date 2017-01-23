#ifndef GRID_H_
#define GRID_H_

//#include "SHIP.H"
#include <utility>
#include <stdexcept>


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
	class bad_range : public std::logic_error
	{
	private:
		coords br;
	public:
		explicit bad_range(coords ix, const std::string & s = "Out of range in Grid object \n");
		coords bi_val() const { return br; }
		virtual ~bad_range() {};
	};
	Grid();
	bool isAvaliable(coords);
	Ship * getShip(coords crd) { return Places[crd.first][crd.second].ShipHere; }
	void setPlace(Ship* ship, coords);
	void HitOrMiss(coords);
	bool wasShot(coords);
};

#endif // !GRID_H_
