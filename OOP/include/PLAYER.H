#ifndef PLAYER_H_
#define PLAYER_H_


#include <vector>
#include "SHIP.H"
#include "ComputerStrategies.h"

class IUserInterface;


class Player
{
public:
	Player() {};
	void  Set_Player_Ships();
	coords virtual SelectTarget(Ship * usedship) = 0;
	virtual Ship*  SelectShip() = 0; //dlaczego nie moge utwrzyc jej jako virtual ??
	bool CanMove();
	bool  hasShips();
	virtual void Move() = 0;

protected:
	vector<Ship*> Ships;
	Grid *player_grid;
	Grid *oponent_grid;
	bool CrossCheck(const coords & c1, const coords & c2);
	bool CrossCheck(const coords & c1, const coords & c2, const coords & c3);
	virtual void SetThreeFunnelShip() = 0;
	virtual void SetTwoFunnelShip() = 0;
	virtual void SetOneFunnelShip() = 0;
private:
	bool virtual SetShip(int ship_type) = 0;
};

class HumanPlayer :public Player {
public:
	HumanPlayer(Grid* grid_player,Grid* grid_oponent, IUserInterface* UI);
	Ship* SelectShip();
	coords SelectTarget(Ship * usedship);
	void Move();
	bool getGridFlag(int x, int y);
protected:
	IUserInterface* User_interface;
	
private:
	bool SetShip(int ship_type); // to improve
	void SetThreeFunnelShip();
	void SetTwoFunnelShip();
	void SetOneFunnelShip();
};


//text mode interface


class ComputerPlayer :public Player
{
public:
	ComputerPlayer(Strategy * strategy, Grid* grid_player, Grid* grid_oponent);
	Ship* SelectShip();
	coords SelectTarget(Ship * usedship);
	void Move();
protected:
	void SetThreeFunnelShip();
	void SetTwoFunnelShip();
	void SetOneFunnelShip();
private:
	Strategy * strategy;
	bool SetShip(int ship_type); // to improve
};

#endif