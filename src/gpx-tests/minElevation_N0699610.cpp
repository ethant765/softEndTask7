#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( minElevation )

const bool isFile = true;
//CORRECT
//Check for correct value
BOOST_AUTO_TEST_CASE( correctMinElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx",isFile);//get log file as route
   BOOST_CHECK_EQUAL( route.minElevation(), 135);//Test that the correct minimum elevation is returned
}

//check for correct value when elevation intervals are set to 10
BOOST_AUTO_TEST_CASE( correctMinElevation10Interval )
{
   Route route = Route(LogFiles::GPXRoutesDir + "vertical10.gpx",isFile);//get log file as route
   BOOST_CHECK_EQUAL( route.minElevation(), 33);//Test that the correct minimum elevation is returned
}
BOOST_AUTO_TEST_CASE( correctMinElevationFirstAndLast )
{
   Route route = Route(LogFiles::GPXRoutesDir + "increasingThenDecreasingElevation.gpx",isFile);//get log file as route
   BOOST_CHECK_EQUAL( route.minElevation(), 42);//Test that the correct minimum elevation is returned when first and last elevations are lowest

}
BOOST_AUTO_TEST_CASE( correctMinElevationNoChange )
{
   Route route = Route(LogFiles::GPXRoutesDir + "noChangeInElevation.gpx",isFile);//get log file as route
   BOOST_CHECK_EQUAL( route.minElevation(), 58);//Test that the correct minimum elevation is returned when no value for change in elevation is set, should default to zero change.

}
BOOST_AUTO_TEST_CASE( correctDecimal )
{
   Route route = Route(LogFiles::GPXRoutesDir + "floatingPoint.gpx",isFile);//get log file as route
   BOOST_CHECK_EQUAL( route.minElevation(), 39);//Test that the correct minimum elevation is returned when vertical difference is a real number (decimal)

}
//check for correct value when elevation interval is negative
BOOST_AUTO_TEST_CASE( correctNegativeInterval )
{
   Route route = Route(LogFiles::GPXRoutesDir + "negativeInterval5Metres.gpx",isFile);//get log file as route
   BOOST_CHECK_EQUAL( route.minElevation(), 53);//Test that the correct minimum elevation is returned
}
BOOST_AUTO_TEST_CASE( correctLargeElevations )
{
   Route route = Route(LogFiles::GPXRoutesDir + "Rockies.gpx",isFile);//get log file as route
   BOOST_CHECK_EQUAL( route.minElevation(), 4201);//Test that the correct minimum elevation is returned for large elevations (mountains)
}

BOOST_AUTO_TEST_CASE( correctMinimumFirstValue )
{
   Route route = Route(LogFiles::GPXRoutesDir + "minElevationFirstValue.gpx",isFile);//get log file as route
   BOOST_CHECK_EQUAL( route.minElevation(), 52);//Test that the correct minimum elevation is returned when the minimum elevation is the first value

}
BOOST_AUTO_TEST_CASE( correctMinimumFinalValue )
{
   Route route = Route(LogFiles::GPXRoutesDir + "minElevationFinalValue.gpx",isFile);//get log file as route
   BOOST_CHECK_EQUAL( route.minElevation(), 48);//Test that the correct minimum elevation is returned when the minimum elevation is the final value

}
BOOST_AUTO_TEST_CASE( correctCircularRoute )
{
   Route route = Route(LogFiles::GPXRoutesDir + "circle.gpx",isFile);//get log file as route
   BOOST_CHECK_EQUAL( route.minElevation(), 42);//Test that the correct minimum elevation is returned when the the route is circular

}
BOOST_AUTO_TEST_CASE( correctNegativeMinElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "negativeElevation.gpx",isFile);
   BOOST_CHECK_EQUAL( route.minElevation(), -6 );//elevation may be negative
}

//check that elevation deaults to zero when no elevation is in log
BOOST_AUTO_TEST_CASE( elevation_absent ) //maybe an exception check instead
{
   Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx",isFile);
   BOOST_CHECK_EQUAL( route.minElevation(), 0);//If there are no elevations present minElevation should default to zero
}
//EDGE
//ensure minElevation takes very low values
BOOST_AUTO_TEST_CASE( edgeElevationZero )
{
   Route route = Route(LogFiles::GPXRoutesDir + "AHM.gpx",isFile);
   BOOST_CHECK_EQUAL( route.minElevation(), 0);//minimum elevation may be zero, ensure this is found
}
BOOST_AUTO_TEST_CASE( edgeElevationsOne )
{
   Route route = Route(LogFiles::GPXRoutesDir + "vertical1Metre.gpx",isFile);
   BOOST_CHECK_EQUAL( route.minElevation(), 1);//likewise 1
}
BOOST_AUTO_TEST_CASE( edgeSmallElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "verySmallElevation.gpx",isFile);
   BOOST_CHECK_EQUAL( route.minElevation(), 0.000001 );//Test that correct min elevation is found when min elevation is very small

}
BOOST_AUTO_TEST_CASE( edgeSmallNegativeElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "verySmalNegativelElevation.gpx",isFile);
   BOOST_CHECK_EQUAL( route.minElevation(), -0.000001 );//Test that correct min elevation is found when min elevation is a very small negative number

}
BOOST_AUTO_TEST_CASE( veryLargeElevations )
{
   Route route = Route(LogFiles::GPXRoutesDir + "Everest.gpx",isFile);//get log file as route
   BOOST_CHECK_EQUAL( route.minElevation(), 6848);//Test that the correct minimum elevation is returned for very large elevations - starting position is summit of Mount Everest, so cannot be any larger
}

BOOST_AUTO_TEST_SUITE_END()

