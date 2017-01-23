#include <boost/test/unit_test.hpp>
#include "ComputerStrategies.h"
#include "PLAYER.H"
#include "SHIP.H"
#include<cstdlib>
#include<ctime>




BOOST_AUTO_TEST_SUITE(ComputerStrategiesTest)

BOOST_AUTO_TEST_CASE(getTargetLocationTest)
{	
	srand(time(NULL));
	Greedy_strategy teststrategy;
	Grid testgrid;
	SingleFunnelShip testship(&testgrid);
	MultiFunnelShip testship2(&testgrid, TWO_FUNNEL_SHIP);
	testship2.setCoords(coords(4, 4), coords(5, 4));
	testship.setCoords(coords(3, 3), coords(3,3));
	for (int i = 0; i < 100; i++)
	{
		BOOST_CHECK_EQUAL(testship.isTargetInRange(teststrategy.getTargetLocation(testship, testgrid)), true);
		BOOST_CHECK_EQUAL(testgrid.wasShot(teststrategy.getTargetLocation(testship2, testgrid)), false);

	}
	

	testgrid.HitOrMiss(coords(2, 2));
	testgrid.HitOrMiss(coords(4, 4));

	for (int i = 0; i < 100; i++)
	{
		BOOST_CHECK_EQUAL(testgrid.wasShot(teststrategy.getTargetLocation(testship, testgrid)), false);
		BOOST_CHECK_EQUAL(testgrid.wasShot(teststrategy.getTargetLocation(testship2, testgrid)), false);
		
	}
}


BOOST_AUTO_TEST_CASE(GreedySelectShipTest)
{
	Greedy_strategy teststrategy;
	Grid testgrid;
	Grid testgrid2;
	SingleFunnelShip testship(&testgrid);
	MultiFunnelShip testship2(&testgrid, TWO_FUNNEL_SHIP);
	MultiFunnelShip testship3(&testgrid, THREE_FUNNEL_SHIP);
	testship.setCoords(coords(1, 1), coords(1, 1));
	testship2.setCoords(coords(3, 3), coords(3, 4));
	testship3.setCoords(coords(7, 9), coords(9, 9));
	vector<Ship*> Ships;
	Ships.push_back(&testship);
	Ships.push_back(&testship2);
	Ships.push_back(&testship3);
	BOOST_CHECK_EQUAL(teststrategy.SelectShip(Ships), &testship3);
	testship3.Shot(coords(7, 7));
	testship3.Shot(coords(7, 8));
	BOOST_CHECK_EQUAL(teststrategy.SelectShip(Ships), &testship2);
	testship3.Reset();
	BOOST_CHECK_EQUAL(teststrategy.SelectShip(Ships), &testship2);
	testship3.Reset();
	BOOST_CHECK_EQUAL(teststrategy.SelectShip(Ships), &testship3);

}


BOOST_AUTO_TEST_SUITE_END()