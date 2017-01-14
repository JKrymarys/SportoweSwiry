#ifndef GAME_H_
#define GAME_H_

#include "PLAYER.H"
#include <vector>
#include <stdexcept>

class Game
{
public:
	Game(int max_rounds, string player1, string player2, bool TextUI);
	Game(bool TextUI);
	~Game();
	void StartGame();
	void AddPlayer( string type, Grid* grid_player, Grid* grid_oponent, bool text_mode);
	void PlayRound();
	void EndGame(int);
	int getCurrentRound();
	int getMaxRound();
	void SaveToFile();
	class Load_From_File_Error : public std::logic_error
	{
	private:
	public:
		explicit Load_From_File_Error(const std::string & s = "Corrupted File, sorry \n") : std::logic_error(s) {}
		virtual ~Load_From_File_Error() {};
	};

private:
	int RoundCount;
	int RoundMAX;
	vector<Player*> Players;
	IUserInterface * UI;
	Grid grid_player1;
	Grid grid_player2;
};

#endif
