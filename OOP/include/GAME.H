#ifndef GAME_H_
#define GAME_H_

#include "PLAYER.H"
#include <vector>

class Game
{
public:
	Game(int max_rounds, string player1, string player2, bool TextUI);
	void StartGame();
	void AddPlayer( string type, Grid* grid_player, Grid* grid_oponent, bool text_mode);
	void PlayRound();
	void EndGame();
	int getCurrentRound();
	int getMaxRound();
	void PrintGrid(bool first_grid);

private:
	int RoundCount;
	int RoundMAX;
	vector<Player*> Players;
	IUserInterface * UI;
	Grid* grid_player1;
	Grid* grid_player2;
};

#endif
