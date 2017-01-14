#ifndef HumanPlayer_H_
#define HumanPlayer_H_

#include "Player.H"

class HumanPlayer :public Player {
public:
	HumanPlayer(Grid* grid_player, Grid* grid_oponent, IUserInterface* UI) : Player(grid_player, grid_oponent), User_interface(UI), wantToMove(true) {}
	virtual ~HumanPlayer();
	Ship* SelectShip();
	coords SelectTarget(Ship * usedship);
	void Move();
	bool CanMove();
	void Reset();
protected:
	IUserInterface* User_interface;
	bool wantToMove;

private:
	void SetThreeFunnelShip();
	void SetTwoFunnelShip();
	void SetOneFunnelShip();
};

#endif // !HumanPlayer_H_
