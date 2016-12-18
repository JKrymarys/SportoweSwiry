#ifndef ComputerStrategies_H_
#define ComputerStrategies_H_


class Strategy {
public:
	virtual void getTargetLocation() = 0;
	Ship* SelectShip();
	void getShipLocation();
};

class Greedy_strategy :public Strategy {
public:
	void getTargetLocation() {} // FOR NOW
};

class Random_strategy : public Strategy {
public:
	void getTargetLocation() {} // FOR NOW 
};


#endif // !ComputerStrategies_H_
