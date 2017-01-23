#ifndef TEXTUI_H_
#define TEXTUI_H_

#include "PLAYER.H"
#include <iostream>
typedef pair<int, int> coords;


class IUserInterface {
public:
	virtual int SelectShip() = 0; // returns type o ship
	virtual coords getTargetLocation() = 0;
	virtual coords getCoords() = 0; // used to place ships
	virtual bool getBool() = 0;
	virtual void printGrid(Grid *, bool whole) = 0;
	virtual void PrintText(string  string) = 0;
	virtual void AskToSave() = 0;
	virtual void ShowStatisticAndWinner(Player * player1, Player * player2) = 0;
	virtual void ShowEndReason(int reason) = 0;

};

class TextUI : public IUserInterface {
public:
	TextUI();
	~TextUI() {}
	int SelectShip(); // returns type o ship
	coords getTargetLocation();
	coords getCoords(); // used to place ships
	void printGrid(Grid *, bool whole);
	void PrintText(string  string);
	bool getBool();
	virtual void AskToSave();
	virtual void ShowStatisticAndWinner(Player * player1, Player * player2);
	virtual void ShowEndReason(int reason);


};

#endif