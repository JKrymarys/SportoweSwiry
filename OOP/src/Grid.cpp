#include <iostream>
#include "GRID.H"
#include "SHIP.H"
#include <string>
#include <cmath>
#include <algorithm>

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
	ship->getHit();
	Places[crd.first][crd.second].Flag = 1;
}

void Grid::Miss(coords crd)
{
	Places[crd.first][crd.second].Flag = 1;
}

Grid::Grid()
{
	// Kazdy elaement array bedzie automatycznie zainicjalizowany uzywajac domyslnego constructora takze nic nie trza
}

bool Grid::isAvaliable(coords crd)
{
	if (crd.first < 0 || crd.second < 0 || crd.first > 9 || crd.second > 9)
		throw bad_range(crd, "Coordinates are out of range of grid in is avaliable function \n" );
	return Places[crd.first][crd.second].ShipHere == nullptr ? true : false;
}



void Grid::setPlace(Ship* ship, coords crd)
{
	if (crd.first < 0 || crd.second < 0 || crd.first > 10 || crd.second > 10)
		throw bad_range(crd, "Coordinates are out of range of grid in in setPlace function \n");
	Places[crd.first][crd.second].ShipHere = ship;
}

void Grid::HitOrMiss(coords crd)
{
	if (crd.first < 0 || crd.second < 0 || crd.first > 9 || crd.second > 9)
		throw bad_range(crd);
	if (Places[crd.first][crd.second].Flag == 1)
		throw bad_range(crd, "Place was already shot");
	Places[crd.first][crd.second].ShipHere == nullptr ? Miss(crd) : Hit(Places[crd.first][crd.second].ShipHere, crd);
};

bool Grid::wasShot(coords crd)
{
	if (crd.first < 0 || crd.second < 0 || crd.first > 9 || crd.second > 9)
		throw bad_range(crd);
	return Places[crd.first][crd.second].Flag == 1 ? true : false;
}

