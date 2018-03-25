#include <boost/test/unit_test.hpp>
#include <iostream>
#include "logs.h"
#include "track.h"
#include "types.h"

using namespace GPS;
const bool isFileName = true;

BOOST_AUTO_TEST_SUITE( MaxRateOfDescentTests )

//Correctness logic tests
/*The first set of test cases that should be tested for are the correctness tests. These tests are for making sure that the logic is correct within the function. For example if the function was made up of:
    a + b = c
    return c
then with an input of a = 2 and b = 3 there should be an output of 5.
In this particular function the point of it is to return the greatest change between two different points in a track, but only for descent.
*/
BOOST_AUTO_TEST_CASE( correctnesstest_zero_elevation )
{
   BOOST_CHECK_EQUAL( Track(LogFiles::GPXTracksDir + "A1B3C.gpx", isFileName).maxRateOfDescent(), 0.0 );
}

BOOST_AUTO_TEST_CASE( correctnesstests_elevation_down )
{
    BOOST_CHECK_EQUAL( Track(LogFiles::GPXTracksDir + "changingelevationnegative.gpx", isFileName).maxRateOfDescent(), -4.0 );
}

BOOST_AUTO_TEST_CASE( correctnesstests_elevation_up )
{
    BOOST_CHECK_EQUAL( Track(LogFiles::GPXTracksDir + "changingelevationpositive.gpx", isFileName).maxRateOfDescent(), 0.0 );
}

//
BOOST_AUTO_TEST_CASE( largest_value_initial )
{

}

BOOST_AUTO_TEST_CASE( largest_value_subtract )
{

}

BOOST_AUTO_TEST_CASE( lowest_value_initial )
{

}

BOOST_AUTO_TEST_CASE( lowest_value_subtract )
{

}

BOOST_AUTO_TEST_SUITE_END()
