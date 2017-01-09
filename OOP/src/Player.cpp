#include "PLAYER.H"
#include <iostream>
#include <vector>
#include "SHIP.H"
#include "ComputerStrategies.h"
#include "TEXTUI.H"

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
	if ((c1.first == c2.first) || (c1.second == c2.second))
		return true;
	else
		return false;
}

bool Player::CrossCheck(const coords & c1, const coords & c2, const coords & c3)
{
	if ((c1.first == c2.first == c3.first )|| (c1.second == c2.second == c3.second))
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

/*
	ComputerPlayer

*/



void ComputerPlayer::Move()
{
	
	Ship * usedship = SelectShip(); // THESE FUNCTION THEMSELVES CHECK IF EVERYTHING IS CORRECT
	
	coords Target = SelectTarget(usedship);
	
	usedship->Shot(Target);
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
			for (int i = start_x - 1; i <= start_x + 2; i++)
				for (int j = y - 1; j <= y+1 ; j++)
					if (j <=9 && i <= 9 && j >=0 && i >= 0 &&!player_grid->isAvaliable(coords(i, j)))
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
			for (int i = x - 1; i <= x+1; i++)
				for (int j = start_y - 1; j < start_y + 2; j++)
					if (j <= 9 && i <= 9 && j >= 0 && i >= 0 && !player_grid->isAvaliable(coords(i, j)))
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
	do
	{
		isOK = true;
		x = rand() % 10;
		y = rand() % 10;
		for (int i = x - 1; i <= x + 1; ++i)
			for (int j = y - 1; j <= y + 1; ++j)
				if (j <= 9 && i <= 9 && j >= 0 && i >= 0 && !player_grid->isAvaliable(coords(i, j)))
					isOK = false;
	} while (!isOK);
	Ships.push_back(new_ship);
	new_ship->setCoords(coords(x, y), coords(x, y));
	player_grid->setPlace(new_ship, coords(x, y));
	
}


Ship* ComputerPlayer::SelectShip()
{
	return strategy->SelectShip(this->Ships);
	//tymczasowo
}


coords ComputerPlayer::SelectTarget(Ship* usedship) {
	return strategy->getTargetLocation((*usedship), *player_grid);
}

/*
	HumanPlayer

*/




void HumanPlayer::Move()
{
	Ship * usedship = nullptr;
	while (usedship == nullptr)
	{
		Ship * usedship = SelectShip();
	}
	// select ship should return nullptr if user wanted to use ship that can't shot 
	coords Target = SelectTarget(usedship);
	while (!usedship->isTargetInRange(Target))
	{
		cout << "Given coordinates are not in range of choosen ship";
		Target = SelectTarget(usedship);
	}
	usedship->Shot(Target);
}

coords HumanPlayer::SelectTarget(Ship * usedship)
{
	return User_interface->getTargetLocation();
}

Ship* HumanPlayer::SelectShip() {
	int type = User_interface->SelectShip();
	
	for (auto i : Ships)
	{
		if (i->getType() == type && i->CanShoot())
			return i;
	}
	cout << "no such a ship" << endl;
	return nullptr;
}


// getPair to grid, and allote there adress coresponding to proper ship

// Trzeba jeszcze dodac sprawdzanie czy nie chce stawiac po przekatnej

/*bool HumanPlayer::SetShip(int ship_type) {
	Ship* new_ship;
	

	if (ship_type = ONE_FUNNEL_SHIP)
		new_ship = new SingleFunnelShip(player_grid);
	else if (ship_type == TWO_FUNNEL_SHIP || ship_type == THREE_FUNNEL_SHIP)
		new_ship = new MultiFunnelShip(player_grid, ship_type);
	
	coords * ship_location = new coords[ship_type];
	bool isOK = true;
	
	do 
	{
		try
		{
			for (int i = 0; i < ship_type; i++)
			{
				ship_location[i] = User_interface->getCoords();
				if (!player_grid->isAvaliable(ship_location[i]))
				{
					isOK = false;
				}
				if (i == 1 && (!CrossCheck(ship_location[0], ship_location[1]))) // sprawdzalem jesli nie sprawdzi sie pierwszy warunek nie bedzie probowal sprawdzic drugiego
				{
					isOK = false;
				}
				if (i == 2 && (!CrossCheck(ship_location[0], ship_location[1], ship_location[2])))
				{
					isOK = false;
				}
				if (!player_grid->canShipBePlaced(ship_location, new_ship, ship_type))
				{
					isOK = false;
				}
			}
		}

		catch (Grid::bad_range & br)
		{
			cout << "excpetion cought" << endl;
			cout << br.what();
			cout << br.bi_val().first << " " << br.bi_val().second;
		}

	} while (isOK);

	this->Ships.push_back(new_ship);//add ship to the vector

	for (int i = 0; i < ship_type; i++)
	{
		player_grid->setPlace(new_ship, ship_location[i]);
		
	}

	return true;
		
}

*/

bool HumanPlayer::getGridFlag(int x, int y)
{
	return player_grid->wasShot(coords(x,y));
}


