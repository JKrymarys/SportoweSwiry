#include <iostream>
#include "GAME.H"
#include "PLAYER.H"
#include "SHIP.H"
#include "GRID.H"

using namespace std;


int main() {
	
	Game game(10,"human","random",true);
	game.StartGame();

	return 0;
}
