#include "PLAYER.H"
#include <iostream>

using namespace std;


/*
	Player

*/


bool Player::hasShips()
{
	if (Ships.size() == 0)
		return false;
	else
		return true;

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

void Player::Move()
{
	Ship * usedship = nullptr;
	while (usedship == nullptr)
	{
		Ship * usedship = SelectShip();
	}
	// select ship should return nullptr if user wanted to use ship that can't shot 
	coords Target = SelectTarget();
	while (!usedship->isTargetInRange(Target))
	{
		cout << "Given coordinates are not in range of choosen ship";
		Target = SelectTarget();
	}
	usedship->Shot(Target);
}



/*
	ComputerPlayer

*/



ComputerPlayer::ComputerPlayer(Strategy * _strategy)
{
	this->strategy = _strategy;
}

bool ComputerPlayer::SetShip(int type) {
	return 0;
	//tymczasowo
}

Ship* ComputerPlayer::SelectShip()
{
	return nullptr;
	//tymczasowo
}
coords ComputerPlayer::SelectTarget() {
	return coords(0,0);
}

/*
	HumanPlayer

*/



HumanPlayer::HumanPlayer() {

	cout << "created" << endl;
}


coords HumanPlayer::SelectTarget()
{
	return User_interface.getTargetLocation();
}

Ship* HumanPlayer::SelectShip() {
	int type = User_interface.SelectShip();
	
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
		new_ship = new SingleFunnelShip(&player_grid);
	else if (ship_type == TWO_FUNNEL_SHIP || ship_type == THREE_FUNNEL_SHIP)
		new_ship = new MultiFunnelShip( &player_grid, ship_type);
	
	coords* ship_location = new coords[ship_type];
	
	for (int i = 0; i < ship_type; i++)
	{
		ship_location[i] = User_interface.getCoords();
		if (!player_grid.isAvaliable(ship_location[i]))
		{
			cout << "This place is not avaliable" << endl;
			return false;
		}
		if (i == 1 && (!CrossCheck(ship_location[0], ship_location[1]))) // sprawdzalem jesli nie sprawdzi sie pierwszy warunek nie bedzie probowal sprawdzic drugiego
			return false;
		if (i == 2 && (!CrossCheck(ship_location[0], ship_location[1], ship_location[2])))
			return false;
	}

	this->Ships.push_back(new_ship);//add ship to the vector
	new_ship->setCoords( ship_location[0], ship_location[ship_type-1]);

	for (int i = 0; i < ship_type; i++)
	{
		player_grid.setPlace(new_ship, ship_location[i]);
		
	}

	return true;
		
}

/*

	HumanInterface

*/

int HumanInterface::SelectShip()
{
	int ship_id = -1;
	cout << "Choose ship:" << endl;
	
	do{
		cin >> ship_id;
	} while (ship_id != 1 || ship_id != 2 || ship_id != 3);

	
	return ship_id;
}

coords HumanInterface::getTargetLocation() {

	int x, y;
	
	cout << "Type coordinates x,y" << endl;
	cin >> x >> y;
	while (x > 10 || y > 10) // should be grid->height, grid ->length
	{
		cout << "Coordinates out of range, retype";
		cin >> x >> y;
	}

	return coords(x, y);

}

coords HumanInterface::getCoords() {
	coords toreturn;

	cout << "Type coordinates x, y " << endl;
	cin >> toreturn.first >> toreturn.second;

	return toreturn;

}