#include "ComputerPlayer.h"
#include <iostream>


void ComputerPlayer::Reset()
{
	for (auto i : Ships)
	{
		i->Reset();
	}
}

ComputerPlayer::~ComputerPlayer()
{
	delete strategy;
}

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
		cerr << err.what() << endl;
		cerr << err.crd_val().first << " " << err.crd_val().second << endl;
	}
	catch (Ship::ship_error err)
	{
		cerr << err.what() << endl;
	}
	catch (Grid::bad_range err)
	{
		cerr << err.what() << endl;
		cerr << err.bi_val().first << " " << err.bi_val().second << endl;
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
			player_grid->setPlace(new_ship, coords(x, start_y + i));

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
				for (int j = LEFT_UPPER_CORNER_Y; j <= RIGHT_LOWER_CORNER_Y; j++)
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
		new_ship->setCoords(coords(x, start_y), coords(x, start_y + 1));
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
	Ship * toreturn = strategy->SelectShip(Ships);
	if (toreturn == nullptr)
		throw Ship::ship_error("None of the ships is avaliable");
	return toreturn;
}

coords ComputerPlayer::SelectTarget(Ship* usedship) {
	return strategy->getTargetLocation((*usedship), *oponent_grid);
}

bool ComputerPlayer::CanMove()
{
	for (auto i : Ships)
	{
		if (i->CanShoot())
			return true;
	}
	//if not
	return false;
}