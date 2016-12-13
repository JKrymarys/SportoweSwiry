#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include "SHIP.H"
#include "GRID.H"
using namespace std;


 class Player
{
public:
	void virtual SetShip();
	pair<int, int> virtual SelectTarget();
	Ship*  SelectShip(); //dlaczego nie moge utwrzyc jej jako virtual ??
	bool CanMove();
	bool  hasShips();
	
	
 
protected:
	vector<Ship> Ships;
	HumanInterface User_interface;
	Grid player_grid;
};

class HumanPlayer:protected Player {
public:
	HumanPlayer();
	void SetShip(int ship_type);
	Ship* SelectShip();
	pair<int,int> SelectTarget();
};


//text mode interface
class HumanInterface {
public:
	void getShipLocation(int size_of_ship);
	int SelectShip(); // returns type o ship
	coords getTargetLocation();
	coords getCoords();
};

class ComputerPlayer :public Player
{
public:
	ComputerPlayer(Strategy * strategy);
	void SetShip();
	Ship* SelectShip();
	pair<int, int> SelectTarget();
private:
	Strategy * strategy;

};

class Strategy {
public:
	virtual void getTargetLocation() = 0;
	Ship* SelectShip();
	void getShipLocation();
};

class Greedy_strategy:public Strategy {
public:
	void getTargetLocation();
};

class Random_strategy: public Strategy {
public:
	void getTargetLocation();
};
#endif