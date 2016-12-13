#ifndef SHIP_H_
#define SHIP_H_

enum Ship_types
{
	ONE_FUNNEL_SHIP = 1,
	TWO_FUNNEL_SHIP = 2,
	THREE_FUNNEL_SHIP = 3,
};

class Ship {

public:
	Ship(int ship_type);
	bool CanShoot();
	bool isTargetInRange();
	void Shot();
	void getHit();
	void Sink();
	bool isSunk();
	virtual void Reset() = 0;
	int getType();

protected:
	int Lives;
	int RemainingShoots;
	int x_begin;
	int x_end;
	int y_begin;
	int y_end;
	int Lenght;
	int type;


};

class SingleFunnelShip :public Ship
{
public:
	SingleFunnelShip();
	void Reset();
};

class MultiFunnelShip :public Ship
{
public:
	MultiFunnelShip();
	void Reset();
};
#endif // !SHIP_H_
