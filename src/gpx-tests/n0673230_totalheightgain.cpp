//N0673230
#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( total_Height_Gain )

const bool isFileName = true;

// The elevation of ABCD.gpx is always 0. This means that the totalHeightGain is always going to be 0
//this test checks that the function returns 0 for the ABCD.gpx file.
BOOST_AUTO_TEST_CASE( ABCD_HeightGain )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalHeightGain(), 0 );
}

// The elevation of NorthYorkMoors.gpx changes, and the total should be 285648.
//this test checks that the function returns 285648 for the NorthYorkMoors.gpx file.
BOOST_AUTO_TEST_CASE( North_HeightGain )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalHeightGain(), 285648 );
}

BOOST_AUTO_TEST_SUITE_END()
