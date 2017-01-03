#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include "SHIP.H"
#include "ComputerStrategies.h"


using namespace std;



class HumanInterface {
public:
	void getShipLocation(int size_of_ship);
	int SelectShip(); // returns type o ship
	coords getTargetLocation();
	coords getCoords(); // used to place ships

};

 class Player
{
public:
	Player()  {};
	bool virtual SetShip(int ship_type) = 0;
	coords virtual SelectTarget() = 0 ;
	virtual Ship*  SelectShip() = 0; //dlaczego nie moge utwrzyc jej jako virtual ??
	bool CanMove();
	bool  hasShips();
	virtual void Move();
	
	
protected:
	vector<Ship*> Ships;
	Grid player_grid;	
	bool CrossCheck(const coords & c1, const coords & c2);
	bool CrossCheck(const coords & c1, const coords & c2, const coords & c3);
};

class HumanPlayer:public Player {
public:
	HumanPlayer();
	bool SetShip(int ship_type); // to improve
	Ship* SelectShip();
	pair<int,int> SelectTarget();
	void Move();
protected:
	HumanInterface User_interface;
};


//text mode interface


class ComputerPlayer :public Player
{
public:
	ComputerPlayer(Strategy * strategy);
	bool SetShip(int ship_type); // to improve
	Ship* SelectShip();
	pair<int, int> SelectTarget(Ship * usedship);
	void Move();
private:
	Strategy * strategy;

};

#endif