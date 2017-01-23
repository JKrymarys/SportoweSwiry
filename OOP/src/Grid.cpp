#include <iostream>
#include "GRID.H"
#include "SHIP.H"
#include <string>

//using namespace std;


Place::Place()
{
	Flag = 0;
	ShipHere = nullptr;
}



Grid::bad_range::bad_range(coords range, const std::string & s) : std::logic_error(s), br(range) {

}



void Grid::Hit(Ship * ship, coords crd)
{
	if (crd.first < 0 || crd.second < 0 || crd.first > 9 || crd.second > 9)
		throw bad_range(crd);
	ship->getHit();
	Places[crd.first][crd.second].Flag = 1;
}

void Grid::Miss(coords crd)
{
	if (crd.first < 0 || crd.second < 0 || crd.first > 9 || crd.second > 9)
		throw bad_range(crd);
	Places[crd.first][crd.second].Flag = 1;
}

Grid::Grid()
{
	// Every element of 2D Array will be initialized with default constructor
}

bool Grid::isAvaliable(coords crd)
{
	if (crd.first < 0 || crd.second < 0 || crd.first > 9 || crd.second > 9)
		throw bad_range(crd);
	return Places[crd.first][crd.second].ShipHere == nullptr ? true : false;
}

void Grid::setPlace(Ship* ship, coords crd)
{
	if (crd.first < 0 || crd.second < 0 || crd.first > 9 || crd.second > 9)
		throw bad_range(crd);
	Places[crd.first][crd.second].ShipHere = ship;
}

void Grid::HitOrMiss(coords crd)
{
	if (crd.first < 0 || crd.second < 0 || crd.first > 9 || crd.second > 9)
		throw bad_range(crd);
	Places[crd.first][crd.second].ShipHere == nullptr ? Miss(crd) : Hit(Places[crd.first][crd.second].ShipHere, crd);
};

bool Grid::wasShot(coords crd)
{
	if (crd.first < 0 || crd.second < 0 || crd.first > 9 || crd.second > 9)
		throw bad_range(crd);
	return Places[crd.first][crd.second].Flag == 1 ? true : false;
}

