#include <boost/test/unit_test.hpp>

#include "ComplexNumber.h"
#include <cmath>


BOOST_AUTO_TEST_SUITE(ComplexNumberTests)

BOOST_AUTO_TEST_CASE(calculateABSvalue_xy4and3_result5)
{
	ComplexNumber z(3.0, 6.0);
	double wynik = z.abs();
	BOOST_CHECK_EQUAL(5.0, wynik);
}

BOOST_AUTO_TEST_SUITE_END()