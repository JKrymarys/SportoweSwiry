#ifndef ComputerStrategies_H_
#define ComputerStrategies_H_

#include<utility>
#include<vector>

using namespace std;

typedef pair<int, int>  coords;
class Grid;
class Ship;

class Strategy {
public:
	coords getTargetLocation(Ship & ship, Grid & grid);
	virtual Ship* SelectShip(vector<Ship*> & Ships) = 0;
};

class Greedy_strategy :public Strategy {
public:
	virtual Ship* SelectShip(vector<Ship*> & Ships);
};

class Random_strategy : public Strategy {
public:
	virtual Ship* SelectShip(vector<Ship*> & Ships);
};


#endif // !ComputerStrategies_H_
