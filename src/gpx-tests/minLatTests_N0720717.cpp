#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

const bool isFileName = true;
// Tests the minimum latitude for NorthYorkMoor.gpx
BOOST_AUTO_TEST_SUITE( premadeGPX_Test )
// Will get the minimum latitdue inside NorthYorkMoor.gpx file
BOOST_AUTO_TEST_CASE( rNorthYorkMoors_Test){
   Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
   BOOST_CHECK_EQUAL(route.minLatitude(), 54.40498352050781);
}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////////////////

// Will test for different min lat being positive, negative, and out of range
BOOST_AUTO_TEST_SUITE( InsideLatRange )
// Testing with positive latitudes
BOOST_AUTO_TEST_CASE(positiveLat){
   Route route = Route(LogFiles::GPXRoutesDir + "N0720717_positveMinLat.gpx", isFileName);
   BOOST_CHECK_GT( route.minLatitude(), 0);
}
// Testing with negative latitudes
BOOST_AUTO_TEST_CASE(negativeLat){
   Route route = Route(LogFiles::GPXRoutesDir + "N0720717_negativeMinLat.gpx", isFileName);
   BOOST_CHECK_LT( route.minLatitude(), 0);
}
// Testing with latitude as 0
BOOST_AUTO_TEST_CASE(zeroLat){
   Route route = Route(LogFiles::GPXRoutesDir + "N0720717_zeroMinLat.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minLatitude(), 0);
}
// Testing with latitude over 90deg
BOOST_AUTO_TEST_CASE(overLat){
   Route route = Route(LogFiles::GPXRoutesDir + "N0720717_overtopedgeMinLat.gpx", isFileName);
   BOOST_CHECK_THROW( route.minLatitude(), std::out_of_range);
}
// Testing with latitude under -90deg
BOOST_AUTO_TEST_CASE(underLat){
   Route route = Route(LogFiles::GPXRoutesDir + "N0720717_underbotedgeMinLat.gpx", isFileName);
   BOOST_CHECK_THROW( route.minLatitude,std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////////////////
