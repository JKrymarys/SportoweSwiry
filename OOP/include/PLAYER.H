#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include "SHIP.H"
using namespace std;


class Player
{
public:
	Player();
	~Player();
	vector<Ship> Ships;
	void SetShip();
	bool CanMove();
	Ship* SelectShip();
	void SelectTarget();
	bool hasShips();
 
private:

};

class HumanPlayer:Player {
public:
	HumanPlayer();
	void SetShip();
	Ship* SelectShip();
	void SelectTarget(); // void?? raczej kurwa nie
};

class HumanInterface {
public:
	void getShipLocation();
	void SelectShip();
	void getTargetLocation();
};

#endif