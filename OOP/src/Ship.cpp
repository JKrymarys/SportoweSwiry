#include "SHIP.H"
#include <algorithm>

/*
SHIP
*/

Ship::Ship(int _Lives, int _Length, int remaining_shots, Grid * p_grid) :
	Lives(_Lives), Lenght(_Length), RemainingShoots(remaining_shots), grid(p_grid)
{

}

void Ship::getHit() {
	Lives--;
}

bool Ship::isSunk() {

	if (this->Lives <= 0)
		return true;
	else
		return false;
}



void Ship::setCoords(coords start, coords end) {
	this->x_begin = std::min(start.first, end.first);
	this->x_end = std::max(start.first, end.first);
	this->y_begin = std::min(start.second, end.second);
	this->y_end = std::max(start.second, end.second);


}

bool Ship::hasAvailableMove()
{
	int LEFT_UPPER_CORNER_X = x_begin - Lenght - 1 > 0 ? x_begin - Lenght - 1 : 0;
	int LEFT_UPPER_CORNER_Y = y_begin - Lenght - 1 > 0 ? y_begin - Lenght - 1 : 0;
	int RIGHT_LOWER_CORNER_X = x_end + Lenght + 1 < 9 ? x_end + Lenght + 1 : 9;
	int RIGHT_LOWER_CORNER_Y = y_end + Lenght + 1 < 9 ? y_end + Lenght + 1 : 9;


	for (int i = LEFT_UPPER_CORNER_X; i <= RIGHT_LOWER_CORNER_X; i++)
		for (int j = LEFT_UPPER_CORNER_Y; j <= RIGHT_LOWER_CORNER_Y; j++)
			if (!(grid->wasShot(coords(i, j))))
				return true;

	return false;

}




bool Ship::CanShoot()
{
	if (!isSunk() && this->hasAvailableMove() && RemainingShoots > 0)
		return true;
	else
		return false;
}

void Ship::Shot(coords target) {
	this->grid->HitOrMiss(target);
	RemainingShoots--;
}

bool Ship::isTargetInRange(coords target) {


	int LEFT_UPPER_CORNER_X = x_begin - Lenght - 1 > 0 ? x_begin - Lenght - 1 : 0;
	int LEFT_UPPER_CORNER_Y = y_begin - Lenght - 1 > 0 ? y_begin - Lenght - 1 : 0;
	int RIGHT_LOWER_CORNER_X = x_end + Lenght + 1 < 9 ? x_end + Lenght + 1 : 9;
	int RIGHT_LOWER_CORNER_Y = y_end + Lenght + 1 < 9 ? y_end + Lenght + 1 : 9;

	if ((target.second >= LEFT_UPPER_CORNER_Y && target.second <= RIGHT_LOWER_CORNER_Y) && (target.first >= LEFT_UPPER_CORNER_X && target.first <= RIGHT_LOWER_CORNER_X))
		return true;

	return false;

}


/*
SINGLE_FUNNEL_SHIP
*/

SingleFunnelShip::SingleFunnelShip(Grid* p_grid) :
	Ship(1, 1, 1, p_grid) {
}

void SingleFunnelShip::Reset() {
	this->RemainingShoots = 1;
}


/*
MULTI_FUNNEL_SHIP
*/

MultiFunnelShip::MultiFunnelShip(Grid* p_grid, int  ship_type) :
	Ship(ship_type, ship_type, 2, p_grid), TakenShots(0) {
}

void MultiFunnelShip::Shot(coords target)
{
	this->grid->HitOrMiss(target);
	TakenShots++;
	RemainingShoots--;

}

void MultiFunnelShip::Reset() {
	if (TakenShots == 2)
		RemainingShoots = 1;
	else
		RemainingShoots = 2;

	TakenShots = 0;
}