#include <iostream>
#include "GAME.H"
#include "PLAYER.H"
#include "SHIP.H"
#include "GRID.H"
#include <ctime>

using namespace std;


int main() {
	
	srand(time(NULL));
	Game game(10,"human","greedy",true);
	//Game game(true);

	return 0;
}
