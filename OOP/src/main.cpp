#include <iostream>
#include "GAME.H"
#include "PLAYER.H"
#include "SHIP.H"
#include "GRID.H"
#include <ctime>

using namespace std;


int main() {
	
	srand(time(NULL));
	Game game(10,"human","random",true);
//	game.StartGame();

	return 0;
}
