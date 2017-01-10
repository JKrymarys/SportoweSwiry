#ifndef TEXTUI_H_
#define TEXTUI_H_

//#include "GAME.H"
#include "PLAYER.H"
#include <iostream>
typedef pair<int, int> coords;


class IUserInterface {
public:
//	virtual void getShipLocation(int size_of_ship) = 0;
	virtual int SelectShip() = 0; // returns type o ship
	virtual coords getTargetLocation() = 0;
	virtual coords getCoords() = 0; // used to place ships
	virtual void printGrid(Grid *) = 0;
	virtual void PrintText(string  string) = 0;
};

class TextUI : public IUserInterface {
private:
	Player* player;
public:
	TextUI();
	~TextUI();
	void getShipLocation(int size_of_ship);
	int SelectShip(); // returns type o ship
	coords getTargetLocation();
	coords getCoords(); // used to place ships
	void printGrid(Grid *);
	void PrintText(string  string);

};

#endif