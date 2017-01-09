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
	if (crd.first < 0 || crd.second < 0 || crd.first > 10 || crd.second > 10)
		throw bad_range(crd);
	return Places[crd.first][crd.second].ShipHere == nullptr ? true : false;
}

bool Grid::canShipBePlaced(coords* ship_location, Ship* ship,int ship_type)
{
	
	int x_smaller = std::min(ship_location[0].first, ship_location[ship_type-1].first);
	int x_bigger = std::max(ship_location[0].first, ship_location[ship_type - 1].first);
	int y_smaller = std::min(ship_location[0].second, ship_location[ship_type - 1].second);
	int y_bigger = std::max(ship_location[0].second, ship_location[ship_type - 1].second);

	for (int x = (x_smaller - 1 == 0) ? 0 : x_smaller - 1; x < (x_bigger + 1 > 10) ? 10 : x_bigger; ++x)
	{
		for (int y = (y_smaller - 1 == 0) ? 0 : y_smaller - 1; x < (y_bigger + 1 > 10) ? 10 : y_bigger; ++y)
		{
			if (!this->isAvaliable(coords(x, y))) //spot suspected to be not avaliable
			{
				// if place is occupied by this ship, it is not a problem
				if (ship_type == 1 && ship_location[0].first == x && ship_location[0].second == y) {}
				else if (ship_type == 2 && ship_location[0].first == x && ship_location[0].second == y || ship_type == 1 && ship_location[1].first == x && ship_location[1].second == y) {}
				else if (ship_type == 1 && ship_location[0].first == x && ship_location[0].second == y || ship_location[1].first == x && ship_location[1].second == y || ship_location[2].first == x && ship_location[2].second == y) {}
				else
					return false;
				//Due to KISS rule we have chosen the simplest but unfortunately a bit silly way to perform this check. However it works :) 
			
			}
		}
	}
	return true;
}

void Grid::setPlace(Ship* ship, coords crd)
{
	if (crd.first < 0 || crd.second < 0 || crd.first > 10 || crd.second > 10)
		throw bad_range(crd);
	Places[crd.first][crd.second].ShipHere = ship;
}

void Grid::HitOrMiss(coords crd)
{
	if (crd.first < 0 || crd.second < 0 || crd.first > 10 || crd.second > 10)
		throw bad_range(crd);
	Places[crd.first][crd.second].ShipHere == nullptr ? Miss(crd) : Hit(Places[crd.first][crd.second].ShipHere, crd);
};

bool Grid::wasShot(coords crd)
{
	if (crd.first < 0 || crd.second < 0 || crd.first > 10 || crd.second > 10)
		throw bad_range(crd);
	return Places[crd.first][crd.second].Flag == 1 ? true : false;
}

