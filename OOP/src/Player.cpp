#include "PLAYER.H"
#include <iostream>
#include <vector>
#include "SHIP.H"
#include "ComputerStrategies.h"
#include "TEXTUI.H"
#include <fstream>

using namespace std;



Player::~Player()
{
	for (auto it = Ships.begin(); it != Ships.end(); ++it)
	{
		delete (*it);
	}
}

bool Player::hasShips()
{
	for (auto i : Ships)
	{
		if (!(i->isSunk()))
			return true;
	}
	//if not
	return false;

}

bool Player::hasRemainingPossibilities()
{
	for (auto i : Ships)
	{
		if (i->hasAvailableMove() && !(i->isSunk()))
			return true;
	}
	return false;
}

void Player::Set_Player_Ships()
{
	SetThreeFunnelShip();
	try {
		SetTwoFunnelShip();
	}
	catch (Grid::bad_range br)
	{
		cout << br.what();
		cout << br.bi_val().first << " " << br.bi_val().second << endl;
	}
	try {
		SetOneFunnelShip();
	catch (Grid::bad_range br)
	{
		cout << br.what();
		cout << br.bi_val().first << " " << br.bi_val().second << endl;
	}
}

int Player::NumberOfShots()
{
	int count = 0;
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
			if (oponent_grid->wasShot(coords(i, j)))
				count++;
	return count;
}

int Player::NumberOfHits()
{
	int count = 0;
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
			if (oponent_grid->wasShot(coords(i, j)) && !(oponent_grid->isAvaliable(coords(i,j))))
				count++;
	return count;
}

void Player::Set_Player_Ships_From_File(char * name)
{
	MultiFunnelShip * Three_Funnel = new MultiFunnelShip(oponent_grid, THREE_FUNNEL_SHIP);
	MultiFunnelShip * Two_Funnel = new MultiFunnelShip(oponent_grid, TWO_FUNNEL_SHIP);
	SingleFunnelShip * Single_Funnel = new SingleFunnelShip(oponent_grid);
	Ships.push_back(Three_Funnel);
	Ships.push_back(Two_Funnel);
	Ships.push_back(Single_Funnel);
	int data_int;
	char data_char;
	int TwoFunnelCount = 0;
	int ThreeFunnelCount = 0;
	coords TwoFunnelBegin;
	coords TwoFunnelEnd;
	coords ThreeFunnelBegin;
	coords ThreeFunnelEnd;
	ifstream inFile(name);
	if (inFile.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				inFile >> data_int;
				if (data_int == 1)
				{
					cout << "FOUND ONE FUNNEL SHIP" << endl;
					Single_Funnel->setCoords(coords(j, i), coords(j, i));
					player_grid->setPlace(Single_Funnel, coords(j, i));
				}
				if (data_int == 2)
				{
					cout << "FOUND TWO FUNNEL SHIP" << endl;
					player_grid->setPlace(Two_Funnel, coords(j, i));
					if (TwoFunnelCount == 0)
						TwoFunnelBegin = coords(j, i);
					else
						TwoFunnelEnd = coords(j, i);
					TwoFunnelCount++;
				}
				if (data_int == 3)
				{
					cout << "FOUND THREE FUNNEL SHIP" << endl;
					player_grid->setPlace(Three_Funnel, coords(j, i));
					if (ThreeFunnelCount == 0)
						ThreeFunnelBegin = coords(j, i);
					else if (ThreeFunnelCount == 2)
						ThreeFunnelEnd = coords(j, i);
					ThreeFunnelCount++;
				}

			}
		}
		Two_Funnel->setCoords(TwoFunnelBegin, TwoFunnelEnd);
		Three_Funnel->setCoords(ThreeFunnelBegin, ThreeFunnelEnd);
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				inFile >> data_char;
				if (data_char == '*')
					player_grid->HitOrMiss(coords(j, i));
			}
		}
	}
	else
		throw;
	for (auto i : Ships)
	{
		if (i->getType() == 3)
		{
			inFile >> data_int;
			i->SetRemainingShoots(data_int);
		}
			
	}
	
	for (auto i : Ships)
	{
		if (i->getType() == 2)
		{
			inFile >> data_int;
			i->SetRemainingShoots(data_int);
		}
	}
	for (auto i : Ships)
	{
		if (i->getType() == 1)
		{
			inFile >> data_int;
			i->SetRemainingShoots(data_int);
		}
	}
	
}

void Player::Save_Info_To_File(int player_index) {
	
	string name;
	if (player_index == 0)
	{
		name = "Player1Grid.txt";
	}
	else
		name = "Player2Grid.txt";


	ofstream PlayerGrid(name.c_str());
	
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (player_grid->isAvaliable(coords(j, i)))
				PlayerGrid << '0';
			else
				PlayerGrid << player_grid->getShip(coords(j, i))->getType();
			PlayerGrid << " ";
		}
		PlayerGrid << endl;
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (player_grid->wasShot(coords(j, i)))
				PlayerGrid << '*';
			else
				PlayerGrid << '#';
			PlayerGrid << " ";
		}
		PlayerGrid << endl;
	}
	for (auto i : Ships)
	{
		if (i->getType() == 3)
			PlayerGrid << i->getRemainingShoots() << endl;
	}
	for (auto i : Ships)
	{
		if (i->getType() == 2)
			PlayerGrid << i->getRemainingShoots() << endl;
	}
	for (auto i : Ships)
	{
		if (i->getType() == 1)
			PlayerGrid << i->getRemainingShoots() << endl;
	}
}



