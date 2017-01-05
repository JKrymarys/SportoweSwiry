#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include "PLAYER.H"
#include "GAME.H"

using namespace std;

class Game
{
public:
	Game(int max_rounds, string player1, string player2);
	void StartGame(int _round_limit);
	void AddPlayer(string type);
	void PlayRound();
	void EndGame();
	int getCurrentRound();
	int getMaxRound();

private:
	int RoundCount;
	int ROUND_LIMIT;
	vector<Player*> Players;
};

#endif
