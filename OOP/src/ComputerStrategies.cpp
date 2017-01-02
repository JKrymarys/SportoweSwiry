#include "ComputerStrategies.h"
#include "PLAYER.H"
#include "SHIP.H"
#include <cmath>
#include<algorithm>

coords Strategy::getTargetLocation(Ship & ship, Grid & grid) {
	int x_random_range = 2 * (ship.getLength() + 1) + (ship.getSecondCoords().first - ship.getFirstCoords().first);
	int y_random_range = 2 * (ship.getLength() + 1) + (ship.getSecondCoords().second - ship.getFirstCoords().second);
	x_random_range > 10 ? x_random_range = 10 : 0 ;
	y_random_range > 10 ? y_random_range = 10 : 0 ;
	int x_generated;
	int y_generated;
	do
	{
		x_generated = rand() % x_random_range + 1;
		y_generated = rand() % y_random_range + 1;
	} while (!grid.wasShot(coords(x_generated, y_generated)));
	return coords(x_generated, y_generated);
}



Ship* Greedy_strategy::SelectShip(vector<Ship*> & Ships) {

	std::vector<Ship *>::iterator it = Ships.begin();
	Ship * toreturn;
	do
	{
		toreturn = (*it);
		++it;
	} while (it != Ships.end() && toreturn->CanShoot());
	for (++it; it != Ships.end(); ++it)
	{
		if ((*it)->getLength() > toreturn->getLength() && (*it)->CanShoot())
			toreturn = (*it);
	}
	return toreturn;
}


 Ship* Random_strategy::SelectShip(vector<Ship*> & Ships) {
	 int random = rand() % Ships.size() + 1;
	 while (!Ships.at(random)->CanShoot)
	 {
		 random = rand() % Ships.size() + 1;
	 }
	 return Ships.at(random);
 }