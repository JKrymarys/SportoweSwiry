#ifndef SHIP_H_
#define SHIP_H_

#include "GRID.H"

typedef pair<int, int>  coords;

enum Ship_types
{
	ONE_FUNNEL_SHIP = 1,
	TWO_FUNNEL_SHIP = 2,
	THREE_FUNNEL_SHIP = 3,
};

class Ship {

public:
	bool CanShoot();
	bool isTargetInRange(float lenght, coords coordinates);
	void Shot();
	void getHit();
	void Sink();
	bool isSunk();
	virtual void Reset() = 0;
	int getType();
	void setCoords(coords start_coords, coords end_coords);

protected:
	int Lives;
	int RemainingShoots;
	int x_begin;
	int x_end;
	int y_begin;
	int y_end;
	int Lenght;
	int type;
	Grid* grid;

};

class SingleFunnelShip :public Ship
{
public:
	SingleFunnelShip( Grid* p_grid,coords coordinates);
	void Reset();

};

class MultiFunnelShip :public Ship
{
public:
	MultiFunnelShip(int ship_type, Grid* p_grid, coords coordinates_start, coords coordinates_end);
	void Reset();
private:
	bool ShotTwice;
};
#endif // !SHIP_H_
