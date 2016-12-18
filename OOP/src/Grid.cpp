#include <iostream>
#include "..\include\grid.H"
#include "SHIP.H"
#include <string>

//using namespace std;


Place::Place()
{
	Flag = 0;
	ShipHere = nullptr;
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
	// Kazdy element array bedzie automatycznie zainicjalizowany uzywajac domyslnego constructora takze nic nie trza
}

bool Grid::isAvaliable(coords crd)
{
	return Places[crd.first][crd.second].ShipHere == nullptr ? true : false;
}

void Grid::setPlace(Ship* ship, coords crd)
{
	Places[crd.first][crd.second].ShipHere = ship;
}

void Grid::HitOrMiss(coords crd)
{
	Places[crd.first][crd.second].ShipHere == nullptr ? Miss(crd) : Hit(Places[crd.first][crd.second].ShipHere, crd);
};

bool Grid::wasShot(coords crd)
{
	return Places[crd.first][crd.second].Flag == 0 ? false : true;
}
