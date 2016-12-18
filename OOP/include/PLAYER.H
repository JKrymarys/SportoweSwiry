#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include "SHIP.H"

using namespace std;



class HumanInterface {
public:
	void getShipLocation(int size_of_ship);
	int SelectShip(); // returns type o ship
	coords getTargetLocation();
	coords getCoords();
};

 class Player
{
public:
	Player();
	void virtual SetShip(int ship_type) ;
	coords virtual SelectTarget() ;
	virtual Ship*  SelectShip(); //dlaczego nie moge utwrzyc jej jako virtual ??
	bool CanMove();
	bool  hasShips();
	
	
 
protected:
	vector<Ship*> Ships;
	Grid player_grid;
	bool CrossCheck(coords c1, coords c2);
};

class HumanPlayer:public Player {
public:
	HumanPlayer();
	void SetShip(int ship_type);
	Ship* SelectShip();
	pair<int,int> SelectTarget();
protected:
	HumanInterface User_interface;
};


//text mode interface

class Strategy;

class ComputerPlayer :public Player
{
public:
	ComputerPlayer(Strategy * strategy);
	void SetShip(int ship_type);
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
	void getTargetLocation() {} // FOR NOW
};

class Random_strategy: public Strategy {
public:
	void getTargetLocation() {} // FOR NOW 
};
#endif