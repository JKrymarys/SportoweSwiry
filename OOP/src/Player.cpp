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

void Player::setGrids(Grid* _player_grid, Grid* _oponent_grid)
{
	this->player_grid = _player_grid;
	this->oponent_grid = _oponent_grid; 
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
	bool isOK;
	isOK = this->SetShip(1);
	isOK = this->SetShip(2);
	isOK = this->SetShip(3);
	cout << isOK << endl;
}

/*
	ComputerPlayer

*/



ComputerPlayer::ComputerPlayer(Strategy * _strategy, Grid* _player_grid, Grid* _oponent_grid)
{
	this->strategy = _strategy;
	this->player_grid = _player_grid;
	this->oponent_grid = _oponent_grid;
}

void ComputerPlayer::Move()
{
	
	Ship * usedship = SelectShip(); // THESE FUNCTION THEMSELVES CHECK IF EVERYTHING IS CORRECT
	
	coords Target = SelectTarget(usedship);
	
	usedship->Shot(Target);
}

bool ComputerPlayer::SetShip(int ship_type) {
	Ship* new_ship;
	if(ship_type = ONE_FUNNEL_SHIP)
		new_ship = new SingleFunnelShip(player_grid);
	else if (ship_type == TWO_FUNNEL_SHIP || ship_type == THREE_FUNNEL_SHIP)
		new_ship = new MultiFunnelShip(player_grid, ship_type);

	coords* ship_location = new coords[ship_type];

	enum Directions{horizontal, vertical};

	int direction = rand() % 2;
	int x_begin;
	int y_begin;
	do
	{
		ship_location[0].first = rand() % 11;
		ship_location[0].second = rand() % 11;
	} while (player_grid->isAvaliable(ship_location[0]));
	
	if (ship_type == TWO_FUNNEL_SHIP || ship_type == THREE_FUNNEL_SHIP)
	{
		if (direction == horizontal)
		{
			if (player_grid->isAvaliable(coords(x_begin + 1, y_begin)))
				ship_location[1] = coords(x_begin + 1, y_begin);
		}

		else
			ship_location[1] = coords(x_begin, y_begin + 1);
	
	}
	

	
	this->Ships.push_back(new_ship);//add ship to the vector
	new_ship->setCoords(ship_location[0], ship_location[ship_type - 1]);

	for (int i = 0; i < ship_type; i++)
	{
		player_grid->setPlace(new_ship, ship_location[i]);

	}

	return true;
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



HumanPlayer::HumanPlayer(Grid* _player_grid, Grid* _oponent_grid, IUserInterface* UI) {

	this->player_grid = _player_grid;
	this->oponent_grid = _oponent_grid;
	this->User_interface = UI;
}

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

bool HumanPlayer::SetShip(int ship_type) {
	Ship* new_ship;
	

	if (ship_type = ONE_FUNNEL_SHIP)
		new_ship = new SingleFunnelShip(player_grid);
	else if (ship_type == TWO_FUNNEL_SHIP || ship_type == THREE_FUNNEL_SHIP)
		new_ship = new MultiFunnelShip(player_grid, ship_type);
	
	coords * ship_location = new coords[ship_type];
	
	try
	{
		for (int i = 0; i < ship_type; i++)
		{
			ship_location[i] = User_interface->getCoords();
			if (!player_grid->isAvaliable(ship_location[i]))
			{
				cout << "This place is not avaliable" << endl;
				return false;
			}
			if (i == 1 && (!CrossCheck(ship_location[0], ship_location[1]))) // sprawdzalem jesli nie sprawdzi sie pierwszy warunek nie bedzie probowal sprawdzic drugiego
			{
				cout << "You cannot place your ship across";
				return false;
			}
			if (i == 2 && (!CrossCheck(ship_location[0], ship_location[1], ship_location[2])))
			{
				cout << "You cannot place your ship across";
				return false;
			}

		}
			
	}
	catch (...)
	{
		cout << "excpetion cought" << endl;
	}
	this->Ships.push_back(new_ship);//add ship to the vector



	for (int i = 0; i < ship_type; i++)
	{
		player_grid->setPlace(new_ship, ship_location[i]);
		
	}

	return true;
		
}

bool HumanPlayer::getGridFlag(int x, int y)
{
	return player_grid->wasShot(coords(x,y));
}


