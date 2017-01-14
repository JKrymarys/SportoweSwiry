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
	Ship(int _Lives, int _Length, int remaining_shots, Grid * p_grid);
	virtual ~Ship() {}
	void getHit();
	int getLives() const { return Lives; }
	int getRemainingShoots() const { return RemainingShoots; }
	void SetRemainingShoots(int n) { RemainingShoots = n; }
	int getXbegin() const  { return x_begin; }
	int getXend() const { return x_end; }
	int getYbegin() const { return y_begin; }
	int getYend() const { return y_end; }
	void setCoords(const coords & start_coords,const coords & end_coords);
	bool isSunk() const;
	bool hasAvailableMove() const;
	bool CanShoot() const;
	bool hasShot_thisRound() const { return TakenShots > 0 ? true : false; }
	virtual void Shot(coords coordinates);
	virtual void Reset() = 0;
	int getLength() const { return Lenght; }
	int getType() const { return type; }
	bool isTargetInRange(coords coordinates) const;
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
	int TakenShots;
	Grid* grid;
};

class SingleFunnelShip : public Ship
{
public:
	SingleFunnelShip(Grid* p_grid);
	~SingleFunnelShip() {}
	void Reset();

};

class MultiFunnelShip : public Ship
{
public:
	MultiFunnelShip(Grid* p_grid, int ship_type);
	~MultiFunnelShip() {}
	//virtual void Shot(coords coordinates);
	void Reset();

};

#endif // !SHIP_H_

