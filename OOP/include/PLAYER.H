#ifndef PLAYER_H_
#define PLAYER_H_


#include <vector>
#include "SHIP.H"
#include "ComputerStrategies.h"
#include <string>

class IUserInterface;


class Player
{
public:
	Player(Grid* grid_player, Grid* grid_oponent) : player_grid(grid_player), oponent_grid(grid_oponent) {};
	virtual ~Player();
	void  Set_Player_Ships();
	bool hasRemainingPossibilities();
	void Set_Player_Ships_From_File(char * name);
	void Save_Info_To_File(int player_index);
	coords virtual SelectTarget(Ship * usedship) = 0;
	virtual Ship*  SelectShip() = 0; 
	virtual bool CanMove() = 0;
	bool  hasShips();
	virtual void Move() = 0;
	virtual void Reset() = 0;
	int NumberOfShots();
	int NumberOfHits();

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
};




#endif