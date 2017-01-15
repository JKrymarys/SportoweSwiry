#include "SHIP.H"
#include <algorithm>

/*
SHIP
*/


Ship::Ship(int _Lives, int _Length, int remaining_shots, Grid * p_grid) :
	Lives(_Lives), Lenght(_Length), RemainingShoots(remaining_shots), grid(p_grid), type(_Length), TakenShots(0)
{
}

void Ship::getHit() {
	Lives--;
}

bool Ship::isSunk() const {

	if (this->Lives <= 0)
		return true;
	else
		return false;
}



void Ship::setCoords(const coords & start,const coords & end) {
	this->x_begin = std::min(start.first, end.first);
	this->x_end = std::max(start.first, end.first);
	this->y_begin = std::min(start.second, end.second);
	this->y_end = std::max(start.second, end.second);


}

bool Ship::hasAvailableMove() const
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




bool Ship::CanShoot() const
{
	if (!isSunk() && this->hasAvailableMove() && RemainingShoots > 0)
		return true;
	else
		return false;
}

void Ship::Shot(coords target) {
	if (!isTargetInRange(target))
		throw Ship::bad_coordinates(target);
	if (isSunk())
		throw Ship::ship_error("Ship is already sunk");
	if (!hasAvailableMove())
		throw Ship::ship_error("Ship has no available move");
	if (RemainingShoots <= 0)
		throw Ship::ship_error("Ship does not have any remainging shoots in this turn");

	this->grid->HitOrMiss(target);
	RemainingShoots--;
	TakenShots++;
}

bool Ship::isTargetInRange(coords target) const {


	int LEFT_UPPER_CORNER_X = x_begin - Lenght - 1 > 0 ? x_begin - Lenght - 1 : 0;
	int LEFT_UPPER_CORNER_Y = y_begin - Lenght - 1 > 0 ? y_begin - Lenght - 1 : 0;
	int RIGHT_LOWER_CORNER_X = x_end + Lenght + 1 < 9 ? x_end + Lenght + 1 : 9;
	int RIGHT_LOWER_CORNER_Y = y_end + Lenght + 1 < 9 ? y_end + Lenght + 1 : 9;

	if ((target.second >= LEFT_UPPER_CORNER_Y && target.second <= RIGHT_LOWER_CORNER_Y) && (target.first >= LEFT_UPPER_CORNER_X && target.first <= RIGHT_LOWER_CORNER_X))
		return true;

	return false;

}



Ship::bad_coordinates::bad_coordinates(coords crd, const std::string & s) : std::logic_error(s), crd(crd) {}


/*
SINGLE_FUNNEL_SHIP
*/


SingleFunnelShip::SingleFunnelShip(Grid* p_grid) :
	Ship(1, 1, 1, p_grid){
}

void SingleFunnelShip::Reset() {
	this->RemainingShoots = 1;
	this->TakenShots = 0;
}


/*
MULTI_FUNNEL_SHIP
*/

MultiFunnelShip::MultiFunnelShip(Grid* p_grid, int  ship_type) :
	Ship(ship_type, ship_type, 2, p_grid) { }



void MultiFunnelShip::Reset() {
	if (TakenShots == 2)
		RemainingShoots = 0;
	else
		RemainingShoots = 2;

	//hasShot = false;
	TakenShots = 0;
}