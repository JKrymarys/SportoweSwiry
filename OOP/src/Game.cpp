#include "GAME.H"
#include "TEXTUI.H"
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include "ComputerPlayer.h"
#include "HumanPlayer.h"

enum END_CASES {
	LastRoundPlayed,
	AllShipsSunk,
	NoMoreOptions,
	SaveGame
};


Game::Game(int max_rounds, string player1, string player2, bool UI_text) {
	
	IUserInterface*  ptr = nullptr;
	if (UI_text)
	{
		ptr = new TextUI;
	}
	//else
	//GUI _UI;
	this->UI = ptr;
	
	this->RoundCount = 1;
	this->RoundMAX = max_rounds;
	//Grid * grid1 = new Grid();
	//Grid * grid2 = new Grid();
	//grid_player1 = grid1;
	//grid_player2 = grid2;
	AddPlayer(player1, &grid_player1, &grid_player2, UI_text);
	AddPlayer(player2,&grid_player2, &grid_player1, UI_text);
	
	for (auto i : Players)
	{
		i->Set_Player_Ships();
	}

}

Game::~Game()
{
//	delete grid_player1;
//	delete grid_player2;
	for (auto it = Players.begin(); it != Players.end(); ++it)
	{
		delete (*it);
	}
	delete UI;
}

Game::Game(bool UI_text)
{
	IUserInterface*  ptr = nullptr;
	if (UI_text)
	{
		ptr = new TextUI;
	}
	//else
	//GUI _UI;
	this->UI = ptr;
	ifstream GameStateFile("GameStateSave.txt");
	char data_char;
	int data_int;
	string line;
	int line_count;
	//Grid * grid1 = new Grid();
	//Grid * grid2 = new Grid();
	//grid_player1 = grid1;
	//grid_player2 = grid2;
	if (GameStateFile.is_open())
	{
		GameStateFile >> RoundCount;
		GameStateFile.get();
		GameStateFile >> RoundMAX;
		GameStateFile.get();
		getline(GameStateFile, line);
		if (line == "greedy")
			AddPlayer("greedy", &grid_player1, &grid_player2, UI_text);
		else if(line == "random")
			AddPlayer("random", &grid_player1, &grid_player2, UI_text);
		else if (line == "human")
			AddPlayer("human", &grid_player1, &grid_player2, UI_text);
		else
			throw Game::Load_From_File_Error();
		getline(GameStateFile, line);
		if (line == "greedy")
			AddPlayer("greedy", &grid_player2, &grid_player1, UI_text);
		else if (line == "random")
			AddPlayer("random", &grid_player2, &grid_player1, UI_text);
		else if (line == "human")
			AddPlayer("human", &grid_player2, &grid_player1, UI_text);
		else
			throw Game::Load_From_File_Error();

	}
	Players.at(0)->Set_Player_Ships_From_File("Player1Grid.txt");
	Players.at(1)->Set_Player_Ships_From_File("Player2Grid.txt");

}

int Game::getCurrentRound() {
	return RoundCount;
} 

int Game::getMaxRound() {
	return RoundMAX;
}

void Game::StartGame()
{
	bool if_continue = true;
	int end_case = 0;
	
	do
	{
		if (dynamic_cast<HumanPlayer*>(Players.at(0)) != nullptr)
		{
			UI->AskToSave();
			if (UI->getBool())
			{
				SaveToFile();
				end_case = SaveGame;
				break;
			}
		}

		PlayRound();

		for (auto i : Players)
		{
			i->Reset();
		}

	

		//case 1: last round played
		if (RoundCount >= RoundMAX)
		{
			if_continue = false;
			end_case = LastRoundPlayed;
		}
		//case 2: one of the players has lost its last ship
		if (!Players[0]->hasShips() || !Players[1]->hasShips())
		{
			if_continue = false;
			end_case = AllShipsSunk;
			break;
		}

		//case 3: no more avaliable shots
		for (auto i : Players)
		{
			if (!i->hasRemainingPossibilities())
			{
				if_continue = false;
				end_case = NoMoreOptions;
			}
		}

		RoundCount++;

	}while (if_continue);

	cout << "End game" << endl;
	EndGame(end_case);
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

	while (((Players.at(0)->CanMove() || Players.at(1)->CanMove()))  && Players.at(0)->hasShips() && Players.at(1)->hasShips())
	{
		this->UI->PrintText("****************** \n Round no. : " + to_string(getCurrentRound()) + "\n");

		//debug
		this->UI->PrintText("Player 1  grid \n ----------------\n");
		UI->printGrid(&grid_player1, true);
		this->UI->PrintText("Player 2  grid \n ----------------\n");
		cout << "Computer grid \n ----------------" << endl;
		UI->printGrid(&grid_player2, dynamic_cast<HumanPlayer*>(Players.at(0)) == nullptr);
		//debug

		//first move has to be done
		if (Players.at(0)->CanMove())
			Players.at(0)->Move();
		if (Players.at(1)->CanMove())
			Players.at(1)->Move();


	}

}



void Game::SaveToFile()
{
	ofstream GameState("GameStateSave.txt");
	ofstream Player1Grid("Player1Grid.txt");
	ofstream Player2Grid("Player2Grid.txt");
	GameState << RoundCount << endl;
	GameState << RoundMAX << endl;
	HumanPlayer * hpl;
	ComputerPlayer * cpl;
	Strategy * str;
	for (int i = 0; i < Players.size(); i++)
	{
		hpl = dynamic_cast<HumanPlayer*>(Players.at(i));
		if (hpl != nullptr)
			GameState << "human" << endl;
		else
		{
			cpl = dynamic_cast<ComputerPlayer*>(Players.at(i));
			str = dynamic_cast<Greedy_strategy*>(cpl->getStrategy());
			if (str != nullptr)
				GameState << "greedy" << endl;
			else
				GameState << "random" << endl;
		}
	}
	/*

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (grid_player1->isAvaliable(coords(j, i)))
				Player1Grid << '0';
			else
				Player1Grid << grid_player1->getShip(coords(j, i))->getType();
			Player1Grid << " ";
		}
		Player1Grid << endl;
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (grid_player1->wasShot(coords(j, i)))
				Player1Grid << '*';
			else
				Player1Grid << '#';
			Player1Grid << " ";
		}
		Player1Grid << endl;
	}
	
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (grid_player2->isAvaliable(coords(j, i)))
				Player2Grid << '0';
			else
				Player2Grid << grid_player2->getShip(coords(j, i))->getType();
			Player2Grid << " ";
		}
		Player2Grid << endl;
	}
	

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (grid_player2->wasShot(coords(j, i)))
				Player2Grid << '*';
			else
				Player2Grid << '#';
			Player2Grid << " ";
		}
		Player2Grid << endl;
	}

	*/
	Players.at(0)->Save_Info_To_File(0);
	Players.at(1)->Save_Info_To_File(1);
}

//1 - max rounds; 2 - player lost; 3 - no more moves
void Game::EndGame(int reason)
{
	if (reason == SaveGame) {
		UI->PrintText("GAME HAS BENN SAVED");
		return;
	}

	UI->PrintText("*************** \n Summary of game: \n\n");
	UI->PrintText("Grid of player 1:");
	UI->printGrid(&grid_player1, true);
	UI->PrintText("Grid of player 2:");
	UI->printGrid(&grid_player2, true);
	UI->ShowEndReason(reason);
	UI->ShowStatisticAndWinner(Players.at(0), Players.at(1));

	UI->PrintText("Thank you for playing! ");
}