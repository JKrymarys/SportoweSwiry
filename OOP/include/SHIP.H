#ifndef SHIP_H_
#define SHIP_H_
#include <utility>
#include <stdexcept>
#include "GRID.H"


enum Ship_types
{
	ONE_FUNNEL_SHIP = 1,
	TWO_FUNNEL_SHIP = 2,
	THREE_FUNNEL_SHIP = 3,
};

class Ship {
public:
	Ship(int _Lives, int _Length, int remaining_shots, Grid * p_grid); // http://stackoverflow.com/questions/18479295/member-initializer-does-not-name-a-non-static-data-member-or-base-class
	void getHit();
	int getLives() { return Lives; }
	int getRemainingShoots() { return RemainingShoots; }
	int getXbegin() { return x_begin; }
	int getXend() { return x_end; }
	int getYbegin() { return y_begin; }
	int getYend() { return y_end; }
	void setCoords(coords start_coords, coords end_coords);
	bool isSunk();
	bool hasAvailableMove();
	bool CanShoot();
	virtual void Shot(coords coordinates);
	virtual void Reset() = 0;
	int getLength() { return Lenght; }
	int getType() { return type; }
	bool isTargetInRange(coords coordinates); // to check
	class bad_coordinates : public std::logic_error
	{
	private:
		coords crd;
	public:
		explicit bad_coordinates(coords crd, const std::string & s = "Bad coordinates error\n");
		coords crd_val() const { return crd; }
		virtual ~bad_coordinates() {};
	};
	class ship_error : public std::logic_error
	{
	public:
		explicit ship_error(const std::string & s = "Ship error error\n") : std::logic_error(s) {}
		virtual ~ship_error() {};
	};
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

class SingleFunnelShip : public Ship
{
public:
	SingleFunnelShip(Grid* p_grid);
	void Reset();

};

class MultiFunnelShip : public Ship
{
public:
	MultiFunnelShip(Grid* p_grid, int ship_type);
	virtual void Shot(coords coordinates);
	void Reset();
private:
	int TakenShots;

};

#endif // !SHIP_H_

