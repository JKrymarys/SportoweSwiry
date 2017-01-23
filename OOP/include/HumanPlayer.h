#ifndef HumanPlayer_H_
#define HumanPlayer_H_

#include "PLAYER.H"

class IUserInterface;

class HumanPlayer :public Player {
public:
	HumanPlayer(Grid* grid_player, Grid* grid_oponent, IUserInterface* UI) : Player(grid_player, grid_oponent), User_interface(UI), wantToMove(true) {}
	virtual ~HumanPlayer();
	Ship* SelectShip();
	coords SelectTarget(Ship * usedship);
	void Move();
	bool CanMove();
	void Reset();
private:
	void SetThreeFunnelShip();
	void SetTwoFunnelShip();
	void SetOneFunnelShip();
	bool CrossCheck(const coords & c1, const coords & c2);
	bool CrossCheck(const coords & c1, const coords & c2, const coords & c3);
	IUserInterface* User_interface;
	bool wantToMove;
};

#endif // !HumanPlayer_H_
