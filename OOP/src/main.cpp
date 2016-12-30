#include <iostream>
#include "../include/GAME.H"
#include "../include/PLAYER.H"
#include "../include/SHIP.H"
#include "../include/GRID.H"
using namespace std;


int main() {
	Game game(5,"human","human");
	game.PlayRound();

	return 0;
}
