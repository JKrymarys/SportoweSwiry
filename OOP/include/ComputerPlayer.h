#ifndef ComputerPlayer_H_
#define ComputerPlayer_H_

#include "Player.H"

class ComputerPlayer :public Player
{
public:
	ComputerPlayer(Strategy * strategy_, Grid* grid_player, Grid* grid_oponent) : Player(grid_player, grid_oponent), strategy(strategy_) {}
	virtual ~ComputerPlayer();
	Ship* SelectShip();
	coords SelectTarget(Ship * usedship);
	void Move();
	bool CanMove();
	Strategy * getStrategy() { return strategy; }
	void Reset();
protected:
	void SetThreeFunnelShip();
	void SetTwoFunnelShip();
	void SetOneFunnelShip();
private:
	Strategy * strategy;
};

#endif // !ComputerPlayer_H_
