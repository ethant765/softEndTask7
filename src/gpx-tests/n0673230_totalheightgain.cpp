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

//the maximum elevation is the same as the radius of the earth. If a value exceeds this it shouldn't be counted and an out_of_range error should be thrown.
// this test case uses ExtremeValues.gpx to see if the function throws an error for extreme elevation values.
//if the extreme value causes and error to be throw, then it passes the test.
BOOST_AUTO_TEST_CASE( ExtremeValues_HeightGain )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ExtremeValues.gpx", isFileName);
   BOOST_CHECK_THROW( route.totalHeightGain(), std::out_of_range );
}

//As there is below sea level it is possible that the elevation may be negative.
//This means that the function needs to be able to work out negative elevations as well.
//this test case uses the BelowSeaLevel.gpx file to find out if the function can correctly calculate a negative total elevation for a route below sea level.
//if the elevation is calculated correctly the function passes the test.
BOOST_AUTO_TEST_CASE( BelowSeaLevel_HeightGain )
{
   Route route = Route(LogFiles::GPXRoutesDir + "BelowSeaLevel.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalHeightGain(), -300);
}


BOOST_AUTO_TEST_SUITE_END()
