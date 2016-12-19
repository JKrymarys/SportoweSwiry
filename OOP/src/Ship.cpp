#include "SHIP.H"
#include <cmath>
#include<algorithm>



bool Ship::hasAvailableMove()
{
	int start_x = std::min(this->x_begin, this->x_end);
	int end_x = std::max(this->x_begin, this->x_end);
	int start_y = std::min(this->y_begin, this->y_end);
	int end_y = std::max(this->y_begin, this->y_end);

	int i = start_x - Lenght - 1 > 0 ? start_x - Lenght - 1 : 0;
	int j = start_y - Lenght - 1 > 0 ? start_y - Lenght - 1 : 0;
	int end_i = start_x + Lenght + 1 < 10 ? start_x + Lenght + 1 : 10;
	int end_j = start_y + Lenght + 1 < 10 ? start_y + Lenght + 1 : 10;
	for(; i < end_i; i++)
		for (; j < end_j; j++)
		{
			if (grid->wasShot(coords(i, j)))
				return false;
		}
	return true;

}



bool Ship::CanShoot() {
	if (!isSunk() && CanShoot() && this->hasAvailableMove())
		return true;
	else
		return false;

}

bool Ship::isTargetInRange( coords target ) {

	float range = Lenght+1;

	if (abs(target.first - this->x_begin) <= range || abs(target.first - this->x_end) <= range)
	{
		if (abs(target.second - this->y_begin) <= range || abs(target.second - this->y_end) <= range)
			return true;
	}

	return false;

} //EEEE to chyba tak moze byc ? xd 
// CHYBA TAK ALE BEDZIE TRZEBA TO PODDAC MOCNYM TESTOM

void Ship::Shot(coords target) {
	this->grid->HitOrMiss(target);
}

void Ship::getHit() {
	this->Lives--;
	
	if (Lives == 0)
		this->Sink();
}

void Ship::Sink() {
	//to graphical UI 
}

bool Ship::isSunk(){

	if (!this->Lives)
		return true;
	else 
		return false;
}

int Ship::getType() {
	return this->Lenght;
}

void Ship::setCoords(coords start, coords end) {
	this->x_begin = start.first;
	this->x_end = end.first;
	this->y_begin = start.second;
	this->y_end = end.second;
}





SingleFunnelShip::SingleFunnelShip( Grid* p_grid) {
	
	this->grid = p_grid;
	this->Lives = 1;
	this->Lenght = 1;
	this->RemainingShoots = 1;
}

void SingleFunnelShip::Reset() {
	this->RemainingShoots = 1;
}





MultiFunnelShip::MultiFunnelShip(Grid* p_grid,int  ship_type) {
	this->grid = p_grid;
	this->Lives = 1;
	this->Lenght = 1;
	this->RemainingShoots = ship_type - 1;
	this->ShotTwice = false;
}

void MultiFunnelShip::Reset() {
	if (ShotTwice)
		RemainingShoots = 1;
	else
		RemainingShoots = 2;
	
	ShotTwice = false;
}