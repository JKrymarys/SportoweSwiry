#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include "PLAYER.H"
#include "GAME.H"

using namespace std;

class Game
{
public:
	Game();
	void StartGame(int _round_limit);
	void AddPlayer(string type);
	void PlayRound();
	void EndGame();

private:
	int RoundCount;
	const int ROUND_LIMIT;
	vector<Player*> Players;
};
#endif
