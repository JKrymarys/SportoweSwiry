#ifndef SHIP_H_
#define SHIP_H_

class Ship {

public:
	Ship();
	bool CanShoot();
	bool isTargetInRange();
	void Shot();
	void getHit();
	void Sink();
	bool isSunk();
	void Reset() = 0;


protected:
	int Lives;
	int RemainingShoots;
	int x_begin;
	int x_end;
	int y_begin;
	int y_end;
	int Lenght;


};
#endif // !SHIP_H_
