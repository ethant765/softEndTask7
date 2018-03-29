#include <boost/test/unit_test.hpp>
#include <iostream>
#include "logs.h"
#include "track.h"
#include "types.h"

using namespace GPS;
const bool isFileName = true;

BOOST_AUTO_TEST_SUITE( MaxRateOfDescentTests )

//Correctness logic tests
/* The first set of test cases that should be tested for are the correctness tests. These tests are for making sure that the
logic is correct within the function. For example if the function was made up of:

        a + b = c
        return c

 * then with an input of a = 2 and b = 3 there should be an output of 5.
 * In this particular function the point of it is to return the greatest change between two different points in a track, but
only for descent.
 * Any ascent doesn't count and if there is only ascent then the return value should be zero.
*/
BOOST_AUTO_TEST_CASE( correctnesstest_zero_elevation )
{
   BOOST_CHECK_EQUAL( Track(LogFiles::GPXTracksDir + "A1B3C.gpx", isFileName).maxRateOfDescent(), 0.0 );
}
/* In these test cases the tracks will only have parts where the elevation changes to be lower at points.
 * The output will be different based on the track and will have to be calculated before testing.
 */
BOOST_AUTO_TEST_CASE( correctnesstests_elevation_down )
{
    BOOST_CHECK_EQUAL( Track(LogFiles::GPXTracksDir + "changingelevationnegative.gpx", isFileName).maxRateOfDescent(), -4.0);
}
/* In these test cases the tracks will only have parts where the elevation changes to be higher at points.
 * The expected output should be zero.
 */
BOOST_AUTO_TEST_CASE( correctnesstests_elevation_up )
{
    BOOST_CHECK_EQUAL( Track(LogFiles::GPXTracksDir + "changingelevationpositive.gpx", isFileName).maxRateOfDescent(), 0);
}

//Underflow and overflow tests
/*
    Testing for underflow and overflow error are easy in this case, because the earth has a lowest recorded point. So the function should take that into account, by either throwing
    an error, or capping the lowest return value at (-1,388(lowest point on earth) - 21,942(highest point on earth)).
*/
/* In this test case the track will have an initial value of a large value double.
 */
BOOST_AUTO_TEST_CASE( largest_value_initial )
{
    BOOST_CHECK_EQUAL( Track(LogFiles::GPXTracksDir + "changingelevationlargestvalinit.gpx", isFileName).maxRateOfDescent(), -11000);
}
/* In this test case the track will have the next value be a large value double
 */
BOOST_AUTO_TEST_CASE( largest_value_next )
{
  BOOST_CHECK_EQUAL(Track(LogFiles::GPXTracksDir + "changingelevationnextmaxvalue.gpx", isFileName).maxRateOfDescent(), 0);
}
//In this test case the initial value will be a verry low value double
BOOST_AUTO_TEST_CASE( lowest_value_initial )
{
  BOOST_CHECK_EQUAL( Track(LogFiles::GPXTracksDir + "changingelevationlowestvalinit.gpx", isFileName).maxRateOfDescent(), 0);
}
//In this test case the next value will be a very low value double
BOOST_AUTO_TEST_CASE( lowest_value_next )
{
  BOOST_CHECK_EQUAL(Track(LogFiles::GPXTracksDir + "changingelevationnextlowestvalue.gpx", isFileName).maxRateOfDescent(), 0);
}
//In this test case the first value will be a high value double and the next value will be a low value double
BOOST_AUTO_TEST_CASE( highest_init_value_lowest_next_value )
{

  BOOST_CHECK_EQUAL(Track(LogFiles::GPXTracksDir + "changingelevationnextlowestvalue.gpx", isFileName).maxRateOfDescent(), -23330);
}
//In this test case the first value will be a low value double and the next value will be a high value double
BOOST_AUTO_TEST_CASE( lowest_init_value_lowest_next_value )
{
  //returns zero
  BOOST_CHECK_EQUAL(Track(LogFiles::GPXTracksDir + "changingelevationnextlowestvalue.gpx", isFileName).maxRateOfDescent(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
