#include "HumanPlayer.h"
#include "TEXTUI.H"

bool HumanPlayer::CanMove()
{
	bool to_return = false;
	for (auto i : Ships)
	{
		if (i->CanShoot())
			to_return = true;
	}

	if (to_return && (wantToMove == false))
		to_return = false;
	//if not
	return to_return;
}

HumanPlayer::~HumanPlayer()
{
	delete User_interface;
}

void HumanPlayer::Reset()
{
	for (auto i : Ships)
	{
		i->Reset();
	}
	this->wantToMove = true;
}

void HumanPlayer::Move()
{
	Ship * usedship;
	// select ship should return nullptr if user wanted to use ship that can't shot 
	coords Target;
	//to check if chosen ship have ability to shoot one more time
	bool flag_can_continue = false;
	bool if_continue = true;
	bool hasEvery_Ship_Shot = true;

	//choose ship
	do
	{
		hasEvery_Ship_Shot = true;

		//show user his possibilities
		User_interface->PrintText("Avaliable ships:");
		for (auto i : Ships)
		{
			if (i->CanShoot())
			{
				User_interface->PrintText(to_string(i->getType()) + " Funnel Ship remaining shoots: " + to_string(i->getRemainingShoots()) + ". Has been used already: " + to_string((i->hasShot_thisRound()) ? true : false) + " times ");
				if (!i->hasShot_thisRound())
					hasEvery_Ship_Shot = false;
			}
		}

		if (hasEvery_Ship_Shot)
		{
			User_interface->PrintText("Would you like to continue this round?");
			if (!User_interface->getBool())
			{
				if_continue = false;
				this->wantToMove = false;
				break; //if user has shot from every ship and dont want to shot second time from multi funnel
			}
		}

		//choose ship
		usedship = SelectShip();

		//if usedship is ready to leave loop, set flag
		if (usedship != nullptr)
			(usedship->getRemainingShoots() != 0) ? flag_can_continue = true : flag_can_continue = false;

	} while (usedship == nullptr);

	//if flag is false, player has chosen not to continue round
	while (flag_can_continue)
	{

		User_interface->PrintText("\nYou have chosen ship of type: " + to_string(usedship->getType()) + "\nYou can take " + to_string(usedship->getRemainingShoots()) + " more shoots in this round");

		Target = SelectTarget(usedship);


		//try to shoot
		while (!usedship->isTargetInRange(Target) || oponent_grid->wasShot(Target))
		{
			oponent_grid->wasShot(Target) ? User_interface->PrintText("There was already shot at this coordinates") : User_interface->PrintText("Given coordinates are not in range of choosen ship");
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

		//ask user what to do if he has chosen multifunnel ship with 2 av shoots
		if (usedship->getRemainingShoots() == 1)
		{
			User_interface->PrintText("Would you like to do second shot?");

			if (!User_interface->getBool())
				flag_can_continue = false;
		}
		else if (usedship->getRemainingShoots() == 0)
			flag_can_continue = false;



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
		for (int x = (ship_location.first - 1) < 0 ? 0 : ship_location.first - 1; x <= ((ship_location.first + 1) > 9 ? 9 : ship_location.first + 1) && isOK; ++x)
			for (int y = (ship_location.second - 1) < 0 ? 0 : ship_location.second - 1; y <= ((ship_location.second + 1) > 9 ? 9 : ship_location.second + 1) && isOK; ++y)
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
	Ship* new_ship = new MultiFunnelShip(oponent_grid, TWO_FUNNEL_SHIP);
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
					for (int y = (ship_location[it].second - 1) < 0 ? 0 : ship_location[it].second - 1; y <= ((ship_location[it].second + 1) > 9 ? 9 : ship_location[it].second + 1) && isOK; ++y)
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
	for (int i = 0; i< TWO_FUNNEL_SHIP; ++i)
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

bool HumanPlayer::CrossCheck(const coords & c1, const coords & c2)
{
	if (((c1.first == c2.first) || (c1.second == c2.second)) && (abs(c1.first + c1.second - c2.first - c2.second) == 1))
		return true;
	else
		return false;
}

bool HumanPlayer::CrossCheck(const coords & c1, const coords & c2, const coords & c3)
{
	if (((c1.first == c2.first && c2.first == c3.first) || (c1.second == c2.second && c2.second == c3.second)) && abs(c1.first + c1.second - c3.first - c3.second) == 2)
		return true;
	else
		return false;
}