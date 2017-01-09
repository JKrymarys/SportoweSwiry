#include "GAME.H"
#include "TEXTUI.H"
#include <iostream>
#include <memory>
#include <vector>



Game::Game(int max_rounds, string player1, string player2, bool UI_text) {
	
	IUserInterface*  ptr = nullptr;
	if (UI_text)
	{
		ptr = new TextUI;
		cout << "done" << endl;
	}
	//else
	//GUI _UI;
	this->UI = ptr;
	
	this->RoundCount = 0;
	this->RoundMAX = max_rounds;
	Grid * grid1 = new Grid();
	Grid * grid2 = new Grid();
	grid_player1 = grid1;
	grid_player2 = grid2;
	AddPlayer(player1,grid1,grid2, UI_text);
	AddPlayer(player2,grid2,grid1, UI_text);
	
	//for each (Player* pl in Players)
	//{
	//	pl->Set_Player_Ships();
	//}

	Players.at(1)->Set_Player_Ships();
	cout << "DEBUG:: game constructor done" << endl;
	try {
		PrintGrid(false);
	}
	catch (Grid::bad_range br)
	{
		cout << br.what() << endl;
		cout << br.bi_val().first << " " << br.bi_val().second;
	}

	
}

int Game::getCurrentRound() {
	return RoundCount;
}
int Game::getMaxRound() {
	return RoundMAX;
}


void Game::StartGame()
{
	cout << "DEBUG: start StartGame" << endl;
	bool if_continue = true;

	while (if_continue)
	{
		cout << "round: " << RoundCount << endl;
			PlayRound();
		
		//case 1: last round played
		if (RoundCount >= RoundMAX)
			if_continue = false;

		cout << "check1" << endl;
		//case 2: one of the players has lost its last ship
		if(Players[0]->hasShips() || Players[1]->hasShips())
			if_continue = false;

		cout << "check2" << endl;
		//case 3: no more avaliable shots
		for each(Player* p in Players)
		{
			if (!p->CanMove())
				if_continue = false;

			cout << "check3" << endl;
		}
		RoundCount++;
	}
	cout << "DEBUG: end StartGame" << endl;
}


//as parameter give: human | random | greedy
void Game::AddPlayer(string type, Grid* grid_player, Grid* grid_oponent, bool text_mode)
{
	if (type == "human" && this->Players.size() <= 2)
	{
		IUserInterface* UI = (text_mode) ? new TextUI : new TextUI; // just 4 debiling
		HumanPlayer* player = new HumanPlayer(grid_player, grid_oponent, UI);
		
		Players.push_back(player);

	}
	else if (type == "greedy" && this->Players.size() <= 2)
	{
		Greedy_strategy *strategy = new  Greedy_strategy;
		ComputerPlayer* player = new ComputerPlayer(strategy, grid_player, grid_oponent);
		Players.push_back(player);
	}
	else if (type == "random" && this->Players.size() <= 2)
	{
		Random_strategy* strategy = new Random_strategy;
		ComputerPlayer* player = new ComputerPlayer(strategy, grid_player, grid_oponent);
		Players.push_back(player);
	}
	else
	{
		std::cout << "AddPlayer error: wrong parameter" << std::endl;
	}

	
	
}

void Game::PlayRound()
{
	cout << "DEBUG: start PlayRound no:" <<RoundCount<< endl;
	while (Players.at(0)->CanMove() || Players.at(1)->CanMove())
	{
		if (Players.at(0)->CanMove())
			Players.at(0)->Move();
		if (Players.at(1)->CanMove())
			Players.at(1)->Move();

		cout << "Can Move: P1 " << Players.at(0)->CanMove() << "P2: " << Players.at(0)->CanMove() << endl;
	}
}

void Game::PrintGrid(bool first_grid)
{
	first_grid ? UI->printGrid(grid_player1) : UI->printGrid(grid_player2);
}