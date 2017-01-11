#include "PLAYER.H"
#include <iostream>
#include <vector>
#include "SHIP.H"
#include "ComputerStrategies.h"
#include "TEXTUI.H"
#include <fstream>

using namespace std;


/*
	Player

*/



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

bool Player::CanMove()
{
	for (auto i : Ships)
	{
		if (i->CanShoot()) 
			return true;
	}
	//if not
	return false;
}

bool Player::CrossCheck(const coords & c1, const coords & c2)
{
	if (((c1.first == c2.first) || (c1.second == c2.second)) && (abs(c1.first + c1.second - c2.first - c2.second) == 1))
		return true;
	else
		return false;
}

bool Player::CrossCheck(const coords & c1, const coords & c2, const coords & c3)
{
	if (((c1.first == c2.first && c2.first == c3.first ) || (c1.second == c2.second && c2.second == c3.second)) && abs(c1.first + c1.second - c3.first - c3.second)==2)
		return true;
	else
		return false;
}

void Player::Set_Player_Ships()
{
	SetThreeFunnelShip();
	cout << "Three funnel ship done" << endl;
	try {
		SetTwoFunnelShip();
	}
	catch (Grid::bad_range br)
	{
		cout << br.what();
		cout << br.bi_val().first << " " << br.bi_val().second << endl;
	}
	cout << "Two funnel ship done" << endl;
	try {
		SetOneFunnelShip();

	}
	catch (Grid::bad_range br)
	{
		cout << br.what();
		cout << br.bi_val().first << " " << br.bi_val().second << endl;
	}
	cout << "One funnel ship done" << endl;
}

void Player::Reset()
{
	for (auto i : Ships)
	{
		i->Reset();
	}
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




/*
	ComputerPlayer

*/



void ComputerPlayer::Move()
{
	
	Ship * usedship = SelectShip(); // THESE FUNCTION THEMSELVES CHECK IF EVERYTHING IS CORRECT
	
	coords Target = SelectTarget(usedship);
	
	try
	{
		usedship->Shot(Target);
	}
	catch (Ship::bad_coordinates err)
	{
		cout << err.what() << endl;
		cout << err.crd_val().first << " " << err.crd_val().second << endl;
	}
	catch (Ship::ship_error err)
	{
		cout << err.what() << endl;
	}
	catch (Grid::bad_range err)
	{
		cout << err.what() << endl;
		cout << err.bi_val().first << " " << err.bi_val().second << endl;
	}
}
void ComputerPlayer::SetThreeFunnelShip()
{
	MultiFunnelShip * new_ship = new MultiFunnelShip(oponent_grid, THREE_FUNNEL_SHIP);
	enum Directions {
		HORIZONTALY = 0,
		VERTICALLY = 1,
	};
	int direction = rand() % 2;
	if (direction == HORIZONTALY)
	{
		int start_x = rand() % 8;
		int y = rand() % 10;
		Ships.push_back(new_ship);
		new_ship->setCoords(coords(start_x, y), coords(start_x + 2, y));
		for (int i = 0; i < new_ship->getLength(); i++)
		{
			player_grid->setPlace(new_ship, coords(start_x + i, y));

		}
	}
	if (direction == VERTICALLY)
	{
		int start_y = rand() % 8;
		int x = rand() % 10;
		Ships.push_back(new_ship);
		new_ship->setCoords(coords(x, start_y), coords(x, start_y + 2));
		for (int i = 0; i < new_ship->getLength(); i++)
		{
			player_grid->setPlace(new_ship, coords(x ,start_y+i));

		}
	}

}
void ComputerPlayer::SetTwoFunnelShip()
{
	MultiFunnelShip * new_ship = new MultiFunnelShip(oponent_grid, TWO_FUNNEL_SHIP);
	enum Directions {
		HORIZONTALY = 0,
		VERTICALLY = 1,
	};
	int direction = rand() % 2;
	int LEFT_UPPER_CORNER_X; 
	int LEFT_UPPER_CORNER_Y; 
	int RIGHT_LOWER_CORNER_X;
	int RIGHT_LOWER_CORNER_Y; 
	if (direction == HORIZONTALY)
	{
		int start_x;
		int y;
		bool isOK;
		do
		{
			isOK = true;
			start_x = rand() % 9;
			y = rand() % 10;
			LEFT_UPPER_CORNER_X = (start_x - 1 < 0 ? 0 : start_x - 1);
			LEFT_UPPER_CORNER_Y = (y - 1 < 0 ? 0 : y - 1);
			RIGHT_LOWER_CORNER_X = (start_x + 2 > 9 ? 9 : start_x + 2);
			RIGHT_LOWER_CORNER_Y = (y + 1 > 9 ? 9 : y + 1);
			for (int i = LEFT_UPPER_CORNER_X; i <= RIGHT_LOWER_CORNER_X; i++)
				for (int j = LEFT_UPPER_CORNER_Y; j <= RIGHT_LOWER_CORNER_Y ; j++)
					if (!player_grid->isAvaliable(coords(i, j)))
						isOK = false;

		} while (!isOK);


		Ships.push_back(new_ship);
		new_ship->setCoords(coords(start_x, y), coords(start_x + 1, y));
		for (int i = 0; i < new_ship->getLength(); i++)
		{
			player_grid->setPlace(new_ship, coords(start_x + i, y));

		}
	}
	if (direction == VERTICALLY)
	{
		int start_y;
		int x;
		bool isOK; 
		do
		{
			isOK = true;
			start_y = rand() % 9;
			x = rand() % 10;
			LEFT_UPPER_CORNER_X = (x - 1 < 0 ? 0 : x - 1);
			LEFT_UPPER_CORNER_Y = (start_y - 1 < 0 ? 0 : start_y - 1);
			RIGHT_LOWER_CORNER_X = (x + 1 > 9 ? 9 : x + 1);
			RIGHT_LOWER_CORNER_Y = (start_y + 2 > 9 ? 9 : start_y + 2);
			for (int i = LEFT_UPPER_CORNER_X; i <= RIGHT_LOWER_CORNER_X; i++)
				for (int j = LEFT_UPPER_CORNER_Y; j <= RIGHT_LOWER_CORNER_Y; j++)
					if (!player_grid->isAvaliable(coords(i, j)))
						isOK = false;
		} while (!isOK);

		Ships.push_back(new_ship);
		new_ship->setCoords(coords(x, start_y), coords(x, start_y+1));
		for (int i = 0; i < new_ship->getLength(); i++)
		{
			player_grid->setPlace(new_ship, coords(x, start_y + i));

		}
	}
}
void ComputerPlayer::SetOneFunnelShip()
{
	SingleFunnelShip * new_ship = new SingleFunnelShip(oponent_grid);
	int x;
	int y;
	bool isOK;
	int LEFT_UPPER_CORNER_X;
	int LEFT_UPPER_CORNER_Y;
	int RIGHT_LOWER_CORNER_X;
	int RIGHT_LOWER_CORNER_Y;
	do
	{
		isOK = true;
		x = rand() % 10;
		y = rand() % 10;
		LEFT_UPPER_CORNER_X = (x - 1 < 0 ? 0 : x - 1);
		LEFT_UPPER_CORNER_Y = (y - 1 < 0 ? 0 : y - 1);
		RIGHT_LOWER_CORNER_X = (x + 1 > 9 ? 9 : x + 1);
		RIGHT_LOWER_CORNER_Y = (y + 1 > 9 ? 9 : y + 1);
		for (int i = LEFT_UPPER_CORNER_X; i <= RIGHT_LOWER_CORNER_X; i++)
			for (int j = LEFT_UPPER_CORNER_Y; j <= RIGHT_LOWER_CORNER_Y; j++)
				if (!player_grid->isAvaliable(coords(i, j)))
					isOK = false;
	} while (!isOK);
	Ships.push_back(new_ship);
	new_ship->setCoords(coords(x, y), coords(x, y));
	player_grid->setPlace(new_ship, coords(x, y));
	
}


Ship* ComputerPlayer::SelectShip()
{
	return strategy->SelectShip(this->Ships);
}


coords ComputerPlayer::SelectTarget(Ship* usedship) {
	return strategy->getTargetLocation((*usedship), *oponent_grid);
}

/*
	HumanPlayer

*/




void HumanPlayer::Move()
{
	Ship * usedship;
	do
	{
		usedship = SelectShip();
	} while (usedship == nullptr);
	
	// select ship should return nullptr if user wanted to use ship that can't shot 
	coords Target = SelectTarget(usedship);
	
	while (!usedship->isTargetInRange(Target))
	{
		User_interface->PrintText("Given coordinates are not in range of choosen ship");
		Target = SelectTarget(usedship);
	} 
	
	try
	{
		usedship->Shot(Target);
	}
	catch (Ship::bad_coordinates err)
	{
		cout << err.what() << endl;
		cout << err.crd_val().first << " " << err.crd_val().second << endl;
	}
	catch (Ship::ship_error err)
	{
		cout << err.what() << endl;
	}
	catch (Grid::bad_range err)
	{
		cout << err.what() << endl;
		cout << err.bi_val().first << " " << err.bi_val().second << endl;
	}
}

coords HumanPlayer::SelectTarget(Ship * usedship)
{
	return User_interface->getTargetLocation();
}

Ship* HumanPlayer::SelectShip()
{
	int type = User_interface->SelectShip();
	
	for (auto i : Ships)
	{
		
		if (i->getType() == type && i->CanShoot())
		{
			return i;
		}
	}
	User_interface->PrintText("Invalid ship");
	return nullptr;
}



void HumanPlayer::SetOneFunnelShip()
{
	Ship* new_ship = new SingleFunnelShip(oponent_grid);
	coords ship_location;
	bool isOK;
	User_interface->PrintText("Set One Funnel Ship");
	do
	{
		ship_location = User_interface->getCoords();
		isOK = true;

		//this loop is going to check if there is no other ship in the close neighbourhood  
		// this loop intelligenty check if user want to place ship on the border of grid, and adjust its behavior (by not going out of grid)
		// also by check isOK boolean value it can stop just when some other ship  is detected
		for (int x = (ship_location.first - 1) < 0 ? 0 : ship_location.first - 1; x <= ((ship_location.first + 1) > 9 ? 9 : ship_location.first +1) && isOK; ++x)
			for (int y = (ship_location.second - 1) < 0 ? 0 : ship_location.second - 1; y <= ((ship_location.second + 1) > 9 ? 9 : ship_location.second) && isOK; ++y)
				if (!player_grid->isAvaliable(coords(x, y)))
				{
					isOK = false;
					cout << "Not avaliable" << endl;
				}
	} while (!isOK);

	this->Ships.push_back(new_ship);
	new_ship->setCoords(ship_location, ship_location);
	player_grid->setPlace(new_ship, ship_location);
	User_interface->PrintText("One Funnel Ship has been set");
}

void HumanPlayer::SetTwoFunnelShip()
{
	User_interface->PrintText("Set Two Funnel Ship");
	Ship* new_ship = new MultiFunnelShip(oponent_grid,TWO_FUNNEL_SHIP);
	coords* ship_location = new coords[TWO_FUNNEL_SHIP];
	bool isOK;
	for (int it = 0; it < TWO_FUNNEL_SHIP; ++it)
	{
		do
		{

			isOK = true;
			ship_location[it] = User_interface->getCoords();

			if (it == 1 && ship_location[it] == ship_location[0]) 
			{ 
				User_interface->PrintText("Choose field next to"); 
				isOK = false; 
			}
			else 
			{
				 if (it == TWO_FUNNEL_SHIP - 1 && !CrossCheck(ship_location[0], ship_location[1]))
					{
						User_interface->PrintText("Cross check failed");
						isOK = false;
					}
			}

			if (isOK)
			{
				//this loop is going to check if there is no other ship in the close neighbourhood  
				// this loop intelligenty check if user want to place ship on the border of grid, and adjust its behavior (by not going out of grid)
				// also by check isOK boolean value it can stop just when some other ship  is detected
				for (int x = (ship_location[it].first - 1) < 0 ? 0 : ship_location[it].first - 1; x <= ((ship_location[it].first + 1) > 9 ? 9 : ship_location[it].first + 1) && isOK; ++x)
					for (int y = (ship_location[it].second - 1) < 0 ? 0 : ship_location[it].second -1; y <= ((ship_location[it].second + 1) > 9 ? 9 : ship_location[it].second + 1) && isOK; ++y)
					{
						if (!player_grid->isAvaliable(coords(x, y)))
						{
							isOK = false;
							User_interface->PrintText("Field is not avaliable");
						}

					}
			}

		} while (!isOK);
	}
	this->Ships.push_back(new_ship);
	
	new_ship->setCoords(ship_location[0], ship_location[1]);
	for(int i = 0; i< TWO_FUNNEL_SHIP; ++i)
		player_grid->setPlace(new_ship, ship_location[i]);


	User_interface->PrintText("Two Funnel Ship has been set");
}

void HumanPlayer::SetThreeFunnelShip()
{
	User_interface->PrintText("Set Three Funnel Ship");
	Ship* new_ship = new MultiFunnelShip(oponent_grid, THREE_FUNNEL_SHIP);
	coords* ship_location = new coords[THREE_FUNNEL_SHIP];
	bool isOK;
	for (int it = 0; it < THREE_FUNNEL_SHIP; ++it)
	{
		do
		{
			isOK = true;
			
			ship_location[it] = User_interface->getCoords();

			//check if field has already been chosen to place this ship
			if (it == 1 && ship_location[it] == ship_location[0]) { User_interface->PrintText("Already chosen. Choose field next to"); isOK = false; }
			else if (it == 2 && (ship_location[it] == ship_location[0] || ship_location[it] == ship_location[1])) { User_interface->PrintText("Already chosen. Choose field next to"); isOK = false; }
			else {

				//check if following coords are inline and just next to (2 and all 3)
				if (it == THREE_FUNNEL_SHIP - 2 && !CrossCheck(ship_location[0], ship_location[1]))
				{
					User_interface->PrintText("Cross check failed");
					isOK = false;
				}
				else if (it == THREE_FUNNEL_SHIP - 1 && !CrossCheck(ship_location[0], ship_location[1], ship_location[2]))
				{
					User_interface->PrintText("Cross check failed");
					isOK = false;
				}
			}
		// as three funnel ship is placed first there is no need to perform addictional validation
		} while (!isOK);
	
	}
	this->Ships.push_back(new_ship);

	new_ship->setCoords(ship_location[0], ship_location[2]);
	for (int i = 0; i< THREE_FUNNEL_SHIP; ++i)
		player_grid->setPlace(new_ship, ship_location[i]);


	User_interface->PrintText("Three Funnel Ship has been set");
}


bool HumanPlayer::getGridFlag(int x, int y)
{
	return player_grid->wasShot(coords(x,y));
}


