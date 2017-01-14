#include <iostream>
#include "GAME.H"
#include "PLAYER.H"
#include "SHIP.H"
#include "GRID.H"
#include <ctime>
#include <string>
#include <cstring>
using namespace std;


int main(int argc, char* argv[]) 
{
	
	srand(time(NULL));

	if (argc < 2 || argc > 4)
	{
		cout << "Bad number of arguments";
		return -1;
	}

	if (argc == 2)
	{
		string arg1 = argv[1];
		if (arg1 == "load")
		{
			Game game(true);
			game.StartGame();
		}
		else
			cout << "If you want to load game state the argument should be \"Load\" ";
	}


	if (argc == 3)
	{
		string roundcount = argv[1];
		try
		{
			stoi(roundcount);
		}
		catch (invalid_argument err)
		{
			cout << "First argument must be integer";
			return 0;
		}
		string user2 = argv[2];
		if (stoi(roundcount) > 0 && stoi(roundcount) <= 20)
		{
			if (user2 == "greedy" || user2 == "random")
			{
				Game game(stoi(roundcount), "human", user2, true);
				game.StartGame();
			}
			else
				cout << "Second argument should be greedy or random";
		}
		else 
			cout << "Number of rounds (first argument) must be between 0 and 20";

	}


	if (argc == 4)
	{
		string roundcount = argv[1];
		try
		{
			stoi(roundcount);
		}
		catch (invalid_argument err)
		{
			cout << "First argument must be integer";
			return 0;
		}
		string user1 = argv[2];
		string user2 = argv[3];
		if (stoi(roundcount) > 0 && stoi(roundcount) <= 20)
		{
			if (user1 == "greedy" || user1 == "random")
			{
				if (user2 == "greedy" || user2 == "random")
				{
					Game game(stoi(roundcount), user1, user2, true);
					game.StartGame();
				}
				else
				{
					cout << "Third argument should be greedy or random";
				}
			}
			else
			{
				cout << "Second argument should be greedy or random ";
			}
		}
		else
			cout << "Number of rounds (first argument) must be between 0 and 20";
	}

	
	return 0;
}
