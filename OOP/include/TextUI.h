#ifndef TEXTUI_H_
#define TEXTUI_H_

#include "GAME.H"
#include "PLAYER.H"
#include <iostream>

class TextUI: public HumanInterface
{
private:
	Game thisGame;
	HumanPlayer Hplayer;
public:
	TextUI();
	~TextUI();
	void mainMenu();
	void PlayRound();
	void ShowGrid();
	void Shoot();
	};

#endif