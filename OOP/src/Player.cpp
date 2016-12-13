#include "PLAYER.H"
#include <iostream>

using namespace std;


ComputerPlayer::ComputerPlayer(Strategy * _strategy)
{
	this->strategy = _strategy;
}

bool Player::hasShips()
{
	if (this->Ships.size == 0)
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


pair<int, int> HumanPlayer::SelectTarget()
{
	return User_interface.getTargetLocation;
}

Ship* HumanPlayer::SelectShip() {
	int type = User_interface.SelectShip();
	
	for (auto i : Ships)
	{
		if (i->getType() == type)
			return i;
	}
}


// getPair to grid, and allote there adress coresponding to proper ship
void HumanPlayer::SetShip(int ship_type) {
	Ship* new_ship;

	if (ship_type = ONE_FUNNEL_SHIP)
		new_ship = new SingleFunnelShip();
	else if (ship_type == TWO_FUNNEL_SHIP || ship_type == THREE_FUNNEL_SHIP)
		new_ship = new MultiFunnelShip();
	
	bool flag = true; //check if all fields can take the ship
	coords* ship_location = new coords[ship_type];
	
	//TODO
	//jakies lepsze info dla gracza jak bedzie blad 


	for (int i = 0; i < ship_type; i++)
	{
		ship_location[i] = User_interface.getCoords();
		if (!player_grid.isAvaliable(ship_location[i]))
		{
			flag = false;
			cout << "This place is not avaliable" << endl;
			break;
		}

	}

	if (flag)
	{
		this->Ships.push_back(new_ship);//add ship to the vector
		new_ship->setCoords( ship_location[0], ship_location[ship_type-1]);

		for (int i = 0; i < ship_type; i++)
		{
			player_grid.setPlace(new_ship, ship_location[i]);
			
		}

	}
		
}


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

	return coords(x, y);

}