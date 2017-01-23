#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp> 
#include "ComputerPlayer.h"

BOOST_AUTO_TEST_SUITE(ComputerPlayerTest)

BOOST_AUTO_TEST_CASE(ComputerSetShipTest)
{
	Grid computergrid;
	Grid oponentgrid;
	Strategy * strategy = new Greedy_strategy;
	ComputerPlayer Player(strategy, &computergrid, &oponentgrid);
	Player.Set_Player_Ships();
	int ships_count = 0;
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
		{
			if (!computergrid.isAvaliable(coords(i, j)))
				ships_count++;
		}
	BOOST_CHECK_EQUAL(ships_count, 6);
}

BOOST_AUTO_TEST_CASE(ComputerPlayerMoveTestWithGreedyStrategy)
{
	Grid computergrid;
	Grid oponentgrid;
	Greedy_strategy * strategy = new Greedy_strategy;
	ComputerPlayer Player(strategy, &computergrid, &oponentgrid);
	Player.Set_Player_Ships();
	Player.Move();
	int shots_count = 0;
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
		{
			if (oponentgrid.wasShot(coords(i, j)))
				shots_count++;
		}
	BOOST_CHECK_EQUAL(shots_count, 1);
	BOOST_CHECK_EQUAL(Player.NumberOfShots(), shots_count);
	Player.Move();
	Player.Move();
	Player.Move();
	Player.Move();
	BOOST_CHECK_EQUAL(Player.NumberOfShots(), 5);
	BOOST_CHECK_EQUAL(Player.CanMove(), false);
	BOOST_CHECK_THROW(Player.Move(), Ship::ship_error);
}

BOOST_AUTO_TEST_CASE(ComputerPlayerMoveTestWithRandomStrategy)
{
	Grid computergrid;
	Grid oponentgrid;
	Random_strategy * strategy = new Random_strategy;
	ComputerPlayer Player(strategy, &computergrid, &oponentgrid);
	Player.Set_Player_Ships();
	Player.Move();
	int shots_count = 0;
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
		{
			if (oponentgrid.wasShot(coords(i, j)))
				shots_count++;
		}
	BOOST_CHECK_EQUAL(shots_count, 1);
	BOOST_CHECK_EQUAL(Player.NumberOfShots(), shots_count);
	Player.Move();
	Player.Move();
	Player.Move();
	Player.Move();
	BOOST_CHECK_EQUAL(Player.NumberOfShots(), 5);
	BOOST_CHECK_EQUAL(Player.CanMove(), false);
	BOOST_CHECK_THROW(Player.Move(), Ship::ship_error);
}


BOOST_AUTO_TEST_SUITE_END()