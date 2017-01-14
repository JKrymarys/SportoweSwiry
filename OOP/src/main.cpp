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
	string arg1(argv[1]);
	if (arg1 == "dupa")
		cout << "WOLOLOLO";

	if (argc == 4)
	{
		string roundcount = argv[1];
		string user1 = argv[2];
		string user2 = argv[3];
		if (stoi(roundcount) > 0 && stoi(roundcount) <= 20)
		{
			if (user1 == "greedy" || user1 == "random" || user1 == "human")
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
				cout << "Second argument should be greedy, random or human";
			}
		}
		else
			cout << "Number of rounds must be between 0 and 20";
	}
	else
	{
		cout << "Bad number of arguments";
	}

	/*int max_Rounds = argc;
	string strategy;
	bool isHuman;
	if (argc != 3)
	{
		cout << "Wrong number of parameters" << endl;
		return 0;
	}




	if (argv[2] == "greedy" || argv[2] == "random")
		strategy = argv[2];
	else
	{
		cout << "Wrong name of strategy" << endl;
		return 0;
	}
	if (argv[3])
		Game game(10, "human", strategy, true);
	else
		Game game(10, strategy, strategy, true);
		*/
	//Game game(10, "human", "greedy", true);

	return 0;
}
