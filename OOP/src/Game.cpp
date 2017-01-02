#include "GAME.H"
#include <iostream>


Game::Game(int max_rounds, string player1, string player2) {
	StartGame(max_rounds);
	AddPlayer(player1);
	AddPlayer(player2);

}

int Game::getCurrentRound() {
	return RoundCount;
}
int Game::getMaxRound() {
	return ROUND_LIMIT;
}


void Game::StartGame(int _round_limit)
{
	int ROUND_LIMIT = _round_limit;

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

void Game::PlayRound()
{
	while (Players.at(0)->CanMove() || Players.at(1)->CanMove())
	{
		if (Players.at(0)->CanMove())
			Players.at(0)->Move();
		if (Players.at(1)->CanMove())
			Players.at(1)->Move();
	}
}
