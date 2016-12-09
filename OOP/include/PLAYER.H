#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include "SHIP.H"
using namespace std;


 class Player
{
public:
	void SetShip();
	bool CanMove();
	Ship* SelectShip();
	void SelectTarget();
	bool hasShips();
 
protected:
	vector<Ship> Ships;
};

class HumanPlayer:public Player {
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

class ComputerPlayer :public Player
{
public:
	ComputerPlayer(Strategy * strategy);
	void SetShip();
	Ship* SelectShip();
	void SelectTarget();
private:
	Strategy * strategy;

};

class Strategy {
public:
	virtual void getTargetLocation() = 0;
	Ship* SelectShip();
	void getShipLocation();
};

class Greedy_strategy:Strategy {
public:
	void getTargetLocation();
};

class Random_strategy:Strategy {
public:
	void getTargetLocation();
};
#endif