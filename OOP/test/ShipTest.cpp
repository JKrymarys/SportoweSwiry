#include <boost/test/unit_test.hpp>
#include "SHIP.H"



BOOST_AUTO_TEST_SUITE(ShipTest)


BOOST_AUTO_TEST_CASE(SingleFunnelShipConstructorTest)
{
	Grid testgrid;
	SingleFunnelShip testship(&testgrid);
	BOOST_CHECK_EQUAL(testship.getLives(), 1);
	BOOST_CHECK_EQUAL(testship.getRemainingShoots(), 1);
}

BOOST_AUTO_TEST_CASE(MultiFunnelShipConstructoTest)
{
	Grid testgrid;
	MultiFunnelShip testship2(&testgrid, TWO_FUNNEL_SHIP);
	MultiFunnelShip testship3(&testgrid, THREE_FUNNEL_SHIP);
	BOOST_CHECK_EQUAL(testship2.getLives(), 2);
	BOOST_CHECK_EQUAL(testship2.getRemainingShoots(), 2);
	BOOST_CHECK_EQUAL(testship3.getLives(), 3);
	BOOST_CHECK_EQUAL(testship3.getRemainingShoots(), 2);
}

BOOST_AUTO_TEST_CASE(ShipIsSunkTest)
{
	Grid testgrid;
	MultiFunnelShip testship2(&testgrid, TWO_FUNNEL_SHIP);
	MultiFunnelShip testship3(&testgrid, THREE_FUNNEL_SHIP);
	SingleFunnelShip testship(&testgrid);
	BOOST_CHECK_EQUAL(testship.isSunk(), false);
	BOOST_CHECK_EQUAL(testship2.isSunk(), false);
	BOOST_CHECK_EQUAL(testship3.isSunk(), false);
	testship.getHit();
	BOOST_CHECK_EQUAL(testship.isSunk(), true);
	testship2.getHit();
	testship2.getHit();
	BOOST_CHECK_EQUAL(testship2.isSunk(), true);
	testship3.getHit();
	testship3.getHit();
	testship3.getHit();
	BOOST_CHECK_EQUAL(testship3.isSunk(), true);
}

BOOST_AUTO_TEST_CASE(SingleFunnelShipsetCoordsTest)
{
	Grid testgrid;
	SingleFunnelShip testship(&testgrid);
	coords testcoords_1_1(1, 1);
	testship.setCoords(testcoords_1_1, testcoords_1_1);
	BOOST_CHECK_EQUAL(testship.getXbegin(), 1);
	BOOST_CHECK_EQUAL(testship.getYbegin(), 1);
	BOOST_CHECK_EQUAL(testship.getXend(), 1);
	BOOST_CHECK_EQUAL(testship.getYend(), 1);
}

BOOST_AUTO_TEST_CASE(TwoFunnelShipsetCoordsTest)
{
	Grid testgrid;
	SingleFunnelShip testship(&testgrid);
	SingleFunnelShip testship2(&testgrid);
	coords testcoords_1_1(1, 1);
	coords testcoords_1_2(1, 2);
	testship.setCoords(testcoords_1_1, testcoords_1_2);
	testship2.setCoords(testcoords_1_2, testcoords_1_1);
	BOOST_CHECK_EQUAL(testship.getXbegin(), 1);
	BOOST_CHECK_EQUAL(testship.getYbegin(), 1);
	BOOST_CHECK_EQUAL(testship.getXend(), 1);
	BOOST_CHECK_EQUAL(testship.getYend(), 2);
	BOOST_CHECK_EQUAL(testship2.getXbegin(), 1);
	BOOST_CHECK_EQUAL(testship2.getYbegin(), 1);
	BOOST_CHECK_EQUAL(testship2.getXend(), 1);
	BOOST_CHECK_EQUAL(testship2.getYend(), 2);
}

BOOST_AUTO_TEST_CASE(SingleFunnelShiphasAvailableMoveTest_2_2)
{
	Grid testgrid;
	SingleFunnelShip testship(&testgrid);
	testship.setCoords(coords(2, 2), coords(2, 2));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), true);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 2; j++)
			testgrid.HitOrMiss(coords(i, j));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), true);
	for (int i = 0; i < 5; i++)
		for (int j = 2; j < 5; j++)
		testgrid.HitOrMiss(coords(i, j));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), false);
}

BOOST_AUTO_TEST_CASE(SingleFunnelShiphasAvailableMoveTest_0_0)
{
	Grid testgrid;
	SingleFunnelShip testship(&testgrid);
	testship.setCoords(coords(0, 0), coords(0, 0));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), true);
	for (int i = 0; i < 3; i++)
		for (int j = 1; j < 3; j++)
			testgrid.HitOrMiss(coords(i, j));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), true);
	for (int i = 0; i < 3; i++)
	testgrid.HitOrMiss(coords(i, 0));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), false);
}

BOOST_AUTO_TEST_CASE(SingleFunnelShiphasAvailableMoveTest_9_9)
{
	Grid testgrid;
	SingleFunnelShip testship(&testgrid);
	testship.setCoords(coords(9, 9), coords(9, 9));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), true);
	for (int i = 7; i < 10; i++)
		for (int j = 7; j < 9; j++)
			testgrid.HitOrMiss(coords(i, j));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), true);
	testgrid.HitOrMiss(coords(7, 9));
	testgrid.HitOrMiss(coords(8, 9));
	testgrid.HitOrMiss(coords(9, 9));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), false);
}


BOOST_AUTO_TEST_CASE(TwoFunnelShiphasAvailableMoveTest_4_4_5_4)
{
	Grid testgrid;
	MultiFunnelShip testship(&testgrid, TWO_FUNNEL_SHIP);
	testship.setCoords(coords(4, 4), coords(5, 4));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), true);
	for (int i = 1; i < 9; i++)
		for (int j = 1; j < 4; j++)
			testgrid.HitOrMiss(coords(i, j));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), true);
	for (int i = 1; i < 9; i++)
		for (int j = 5; j < 8; j++)
			testgrid.HitOrMiss(coords(i, j));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), true);
	for (int i = 1; i < 4; i++)
		testgrid.HitOrMiss(coords(i, 4));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), true);
	for (int i = 4; i < 9; i++)
		testgrid.HitOrMiss(coords(i, 4));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), false);
}


BOOST_AUTO_TEST_CASE(TwoFunnelShiphasAvailableMoveTest_8_9_9_9)
{
	Grid testgrid;
	MultiFunnelShip testship(&testgrid, TWO_FUNNEL_SHIP);
	testship.setCoords(coords(8, 9), coords(9, 9));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), true);
	for (int i = 5; i < 10; i++)
		for (int j = 6; j < 9; j++)
			testgrid.HitOrMiss(coords(i, j));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), true);
	for (int i = 5; i < 10; i++)
		testgrid.HitOrMiss(coords(i, 9));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), false);
}

BOOST_AUTO_TEST_CASE(TwoFunnelShiphasAvailableMoveTest_4_4_4_5)
{
	Grid testgrid;
	MultiFunnelShip testship(&testgrid, TWO_FUNNEL_SHIP);
	testship.setCoords(coords(4, 4), coords(4, 5));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), true);
	for (int i = 1; i < 4; i++)
		for (int j = 1; j < 9; j++)
			testgrid.HitOrMiss(coords(i, j));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), true);
	for (int i = 5; i < 8; i++)
		for (int j = 1; j < 9; j++)
			testgrid.HitOrMiss(coords(i, j));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), true);
	for (int i = 1; i < 9; i++)
		testgrid.HitOrMiss(coords(4, i));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), false);
}

BOOST_AUTO_TEST_CASE(TwoFunnelShiphasAvailableMoveTest_9_8_9_9)
{
	Grid testgrid;
	MultiFunnelShip testship(&testgrid, TWO_FUNNEL_SHIP);
	testship.setCoords(coords(9, 8), coords(9, 9));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), true);
	for (int i = 6; i < 10; i++)
		for (int j = 5; j < 8; j++)
			testgrid.HitOrMiss(coords(i, j));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), true);
	for (int i = 6; i < 10; i++)
		testgrid.HitOrMiss(coords(i, 8));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), true);
	for (int i = 6; i < 10; i++)
		testgrid.HitOrMiss(coords(i, 9));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), false);

}

BOOST_AUTO_TEST_CASE(ThreeFunnelShiphasAvailableMoveTest_4_4_6_4)
{
	Grid testgrid;
	MultiFunnelShip testship(&testgrid, THREE_FUNNEL_SHIP);
	testship.setCoords(coords(4, 4), coords(6, 4));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), true);
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 4; j++)
			testgrid.HitOrMiss(coords(i, j));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), true);
	for (int i = 0; i < 10; i++)
		for (int j = 5; j < 9; j++)
			testgrid.HitOrMiss(coords(i, j));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), true);
	for (int i = 0; i < 10; i++)
		testgrid.HitOrMiss(coords(i, 4));
	BOOST_CHECK_EQUAL(testship.hasAvailableMove(), false);
}




BOOST_AUTO_TEST_CASE(ShipCanShootTest)
{
	Grid testgrid;
	SingleFunnelShip testship(&testgrid);
	testship.setCoords(coords(2, 2), coords(2, 2));
	BOOST_CHECK_EQUAL(testship.CanShoot(), true);
	testship.getHit();
	BOOST_CHECK_EQUAL(testship.CanShoot(), false);
}


BOOST_AUTO_TEST_CASE(SingleFunnelShipShootTest)
{
	Grid testgrid;
	SingleFunnelShip test_ship(&testgrid);
	test_ship.setCoords(coords(2, 2), coords(2, 2));
	SingleFunnelShip test_target_ship(&testgrid);
	testgrid.setPlace(&test_target_ship, coords(1, 1));
	test_ship.Shot(coords(1, 1));
	BOOST_CHECK_EQUAL(test_ship.getRemainingShoots(), 0);
	BOOST_CHECK_EQUAL(test_target_ship.getLives(), 0);
}

BOOST_AUTO_TEST_CASE(MultiFunnelShipShootTest)
{
	Grid testgrid;
	MultiFunnelShip test_ship2(&testgrid, TWO_FUNNEL_SHIP);
	MultiFunnelShip test_target_ship(&testgrid, TWO_FUNNEL_SHIP);
	test_ship2.setCoords(coords(2, 2), coords(2, 3));
	testgrid.setPlace(&test_target_ship, coords(1, 1));
	testgrid.setPlace(&test_target_ship, coords(1, 2));
	test_ship2.Shot(coords(1, 1));
	BOOST_CHECK_EQUAL(test_ship2.getRemainingShoots(), 1);
	BOOST_CHECK_EQUAL(test_target_ship.getLives(), 1);
	test_ship2.Shot(coords(1, 3));
	BOOST_CHECK_EQUAL(test_ship2.getRemainingShoots(), 0);
	BOOST_CHECK_EQUAL(test_target_ship.getLives(), 1);

}

BOOST_AUTO_TEST_CASE(SingleFunnelShipResetTest)
{
	Grid testgrid;
	SingleFunnelShip testship(&testgrid);
	testship.setCoords(coords(2, 2), coords(2, 2));
	testship.Shot(coords(1, 1));
	BOOST_CHECK_EQUAL(testgrid.wasShot(coords(1, 1)), true);
	BOOST_CHECK_EQUAL(testship.getRemainingShoots(), 0);
	testship.Reset();
	BOOST_CHECK_EQUAL(testship.getRemainingShoots(), 1);

}

BOOST_AUTO_TEST_CASE(MultiFunnelShipResetTest)
{
	Grid testgrid;
	MultiFunnelShip testship2(&testgrid, TWO_FUNNEL_SHIP);
	testship2.setCoords(coords(2, 2), coords(2, 3));
	testship2.Shot(coords(1, 1));
	BOOST_CHECK_EQUAL(testship2.getRemainingShoots(), 1);
	testship2.Shot(coords(2, 1));
	BOOST_CHECK_EQUAL(testship2.getRemainingShoots(), 0);
	testship2.Reset();
	BOOST_CHECK_EQUAL(testship2.getRemainingShoots(), 0);
	testship2.Reset();
	BOOST_CHECK_EQUAL(testship2.getRemainingShoots(), 2);
	testship2.Shot(coords(3, 1));
	BOOST_CHECK_EQUAL(testship2.getRemainingShoots(), 1);
	testship2.Reset();
	BOOST_CHECK_EQUAL(testship2.getRemainingShoots(), 2);

}

BOOST_AUTO_TEST_CASE(SingleFunnelShipisTargetinRangeTest)
{
	Grid testgrid;
	SingleFunnelShip testship(&testgrid);
	MultiFunnelShip testship2(&testgrid, THREE_FUNNEL_SHIP);
	testship.setCoords(coords(4, 4), coords(4, 4));
	testship2.setCoords(coords(4, 4), coords(6, 4));
	BOOST_CHECK_EQUAL(testship.isTargetInRange(coords(2, 2)), true);
	BOOST_CHECK_EQUAL(testship.isTargetInRange(coords(0, 0)), false);
	BOOST_CHECK_EQUAL(testship.isTargetInRange(coords(4, 4)), true);
	BOOST_CHECK_EQUAL(testship2.isTargetInRange(coords(11, 7)), false);
}

BOOST_AUTO_TEST_SUITE_END()