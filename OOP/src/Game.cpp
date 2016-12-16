#include "GAME.H"
#include <iostream>

void Game::StartGame(int _round_limit)
{
	const int ROUND_LIMIT = _round_limit;

}


//as parameter give: human | random | greedy
void Game::AddPlayer(string type)
{
	if (type == "human" && this->Players.size() <= 2)
	{
		Players.push_back(&HumanPlayer());

	}
	else if (type == "greedy" && this->Players.size() <= 2)
	{
		Greedy_strategy strategy;
		Players.push_back(&ComputerPlayer(&strategy));
	}
	else if (type == "random" && this->Players.size() <= 2)
	{
		Random_strategy strategy;
		Players.push_back(&ComputerPlayer(&strategy));
	}
	else
	{
		std::cout << "AddPlayer error: wrong parameter" << std::endl;
	}

	
	
}
