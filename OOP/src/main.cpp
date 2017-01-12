#include <iostream>
#include "GAME.H"
#include "PLAYER.H"
#include "SHIP.H"
#include "GRID.H"
#include <ctime>
#include <string>
using namespace std;


int main(int argc, char* argv[]) 
{
	
	srand(time(NULL));
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
	Game game(10, "human", "greedy", true);

	return 0;
}
