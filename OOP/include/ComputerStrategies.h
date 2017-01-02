#ifndef ComputerStrategies_H_
#define ComputerStrategies_H_


class Strategy {
public:
	coords getTargetLocation(Ship & ship, Grid & grid);
	virtual Ship* SelectShip(vector<Ship*> & Ships) = 0;
};

class Greedy_strategy :public Strategy {
public:
	virtual Ship* SelectShip(vector<Ship*> & Ships) = 0;
};

class Random_strategy : public Strategy {
public:
	virtual Ship* SelectShip(vector<Ship*> & Ships) = 0;
};


#endif // !ComputerStrategies_H_
