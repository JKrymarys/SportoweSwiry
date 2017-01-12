#include "ComputerStrategies.h"
#include "PLAYER.H"
#include "SHIP.H"
#include <cmath>
#include <algorithm>

coords Strategy::getTargetLocation(Ship & ship, Grid & grid) {

	int LEFT_UPPER_CORNER_X = (ship.getXbegin() - ship.getLength() - 1 > 0 ? ship.getXbegin() - ship.getLength() - 1 : 0);
	int LEFT_UPPER_CORNER_Y = (ship.getYbegin() - ship.getLength() - 1 > 0 ? ship.getYbegin() - ship.getLength() - 1 : 0);
	int RIGHT_LOWER_CORNER_X = (ship.getXend() + ship.getLength() + 1 < 9 ? ship.getXend() + ship.getLength() + 1 : 9);
	int RIGHT_LOWER_CORNER_Y = (ship.getYend() + ship.getLength() + 1 < 9 ? ship.getYend() + ship.getLength() + 1 : 9);

	int x_generated = rand() % (RIGHT_LOWER_CORNER_X - LEFT_UPPER_CORNER_X + 1) + LEFT_UPPER_CORNER_X;
	int y_generated = rand() % (RIGHT_LOWER_CORNER_Y - LEFT_UPPER_CORNER_Y + 1) + LEFT_UPPER_CORNER_Y;

	while (grid.wasShot(coords(x_generated, y_generated)))
	{
		x_generated = rand() % (RIGHT_LOWER_CORNER_X - LEFT_UPPER_CORNER_X + 1) + LEFT_UPPER_CORNER_X;
		y_generated = rand() % (RIGHT_LOWER_CORNER_Y - LEFT_UPPER_CORNER_Y + 1) + LEFT_UPPER_CORNER_Y;

	}
	return coords(x_generated, y_generated);

}



Ship* Greedy_strategy::SelectShip(vector<Ship*> & Ships) {

	Ship * toreturn = nullptr;
	auto it = Ships.begin();
	while (it != Ships.end() || toreturn == nullptr)
	{
		if ((*it)->CanShoot())
			toreturn = (*it);
		++it;
	}
	while (it != Ships.end())
	{
		if (((*it)->getLength() > toreturn->getLength()))
			if ((*it)->CanShoot())
				toreturn = (*it);
		++it;
	}

	return toreturn;
}


Ship* Random_strategy::SelectShip(vector<Ship*> & Ships) {
	int random = rand() % Ships.size();
	while (!Ships.at(random)->CanShoot())
	{
		random = rand() % Ships.size();
	}
	return Ships.at(random);
}