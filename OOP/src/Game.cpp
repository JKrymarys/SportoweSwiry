#include "GAME.H"

void Game::StartGame(int _round_limit)
{
	const int ROUND_LIMIT = _round_limit;

}

void Game::AddPlayer(string type)
{
	if (type == "human" && this->Players.size() <= 2) 		Players.push_back(HumanPlayer());
	else if (type == "greedy" && this->Players.size() <= 2) Players.push_back(ComputerPlayer(true));
	else if (type == "random" && this->Players.size() <= 2) Players.push_back(ComputerPlayer(false));
	
}
