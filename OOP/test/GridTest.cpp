#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp> 
#include "GRID.H"
#include "SHIP.H"

BOOST_AUTO_TEST_SUITE(GridTest)

Grid testgrid;

BOOST_AUTO_TEST_CASE(GridConstructorTest)
{
	
	coords testcoords_1_1(1, 1);
	coords testcoords_3_5(3, 5);
	BOOST_CHECK_EQUAL(testgrid.wasShot(testcoords_1_1), false);
	BOOST_CHECK_EQUAL(testgrid.isAvaliable(testcoords_1_1), true);
	BOOST_CHECK_EQUAL(testgrid.wasShot(testcoords_3_5), false);
	BOOST_CHECK_EQUAL(testgrid.isAvaliable(testcoords_3_5), true);
	
}



BOOST_AUTO_TEST_CASE(wasShotExcepctionTest)
{
	coords testcoords_m1_5(-1, 5);
	coords testcoords_5_m1(5, -1);
	coords testcoords_11_5(11, 5);
	coords testcoords_5_11(5, 11);
	BOOST_CHECK_THROW(testgrid.wasShot(testcoords_m1_5), Grid::bad_range);
	BOOST_CHECK_THROW(testgrid.wasShot(testcoords_5_m1), Grid::bad_range);
	BOOST_CHECK_THROW(testgrid.wasShot(testcoords_11_5), Grid::bad_range);
	BOOST_CHECK_THROW(testgrid.wasShot(testcoords_5_11), Grid::bad_range);
}

BOOST_AUTO_TEST_CASE(isAvaliableExcepctionTest)
{
	coords testcoords_m1_5(-1, 5);
	coords testcoords_5_m1(5, -1);
	coords testcoords_11_5(11, 5);
	coords testcoords_5_11(5, 11);
	BOOST_CHECK_THROW(testgrid.isAvaliable(testcoords_m1_5), Grid::bad_range);
	BOOST_CHECK_THROW(testgrid.isAvaliable(testcoords_5_m1), Grid::bad_range);
	BOOST_CHECK_THROW(testgrid.isAvaliable(testcoords_11_5), Grid::bad_range);
	BOOST_CHECK_THROW(testgrid.isAvaliable(testcoords_5_11), Grid::bad_range);
}




BOOST_AUTO_TEST_CASE(setPlaceTest)
{
	SingleFunnelShip test(&testgrid);
	Ship * testship = &test;
	coords testcoords_1_1(1, 1);
	testgrid.setPlace(testship, testcoords_1_1);
	BOOST_CHECK_EQUAL(testgrid.isAvaliable(testcoords_1_1), false);
}

BOOST_AUTO_TEST_CASE(setPlaceExceptionTest)
{
	SingleFunnelShip test(&testgrid);
	Ship * testship = &test;
	coords testcoords_m1_5(-1, 5);
	coords testcoords_5_m1(5, -1);
	coords testcoords_11_5(11, 5);
	coords testcoords_5_11(5, 11);
	BOOST_CHECK_THROW(testgrid.setPlace(testship, testcoords_m1_5), Grid::bad_range);
	BOOST_CHECK_THROW(testgrid.setPlace(testship, testcoords_5_m1), Grid::bad_range);
	BOOST_CHECK_THROW(testgrid.setPlace(testship, testcoords_11_5), Grid::bad_range);
	BOOST_CHECK_THROW(testgrid.setPlace(testship, testcoords_5_11), Grid::bad_range);
}


BOOST_AUTO_TEST_CASE(HitOrMissTest_Miss)
{
	coords testcoords_1_5(1, 5);
	coords testcoords_m1_5(-1, 5);
	testgrid.HitOrMiss(testcoords_1_5);
	BOOST_CHECK_EQUAL(testgrid.wasShot(testcoords_1_5), true);
	BOOST_CHECK_THROW(testgrid.HitOrMiss(testcoords_m1_5), Grid::bad_range);
}

BOOST_AUTO_TEST_CASE(HitOrMissTest_Hit)
{
	coords testcoords_2_2(2, 2);
	SingleFunnelShip test(&testgrid);
	Ship * testship = &test;
	testgrid.setPlace(testship, testcoords_2_2);
	testgrid.HitOrMiss(testcoords_2_2);
	BOOST_CHECK_EQUAL(test.getLives(), 0);
}

BOOST_AUTO_TEST_SUITE_END()