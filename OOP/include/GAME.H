#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include "PLAYER.H"

using namespace std;

class Game
{
public:
	Game();
	void StartGame();
	void AddPlayer();
	void PlayRound();
	void EndGame();

private:
	int RoundCount;
	const int ROUND_LIMIT;
	vector<Player> Players;
};
#endif
