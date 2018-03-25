#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_MaxLongitude_N0669298 )

const bool isFileName = true;

// A test case to test that the right Longitude is being returned from a GPX file where the gridworld represents a straight line
// The returned Longitude should be the greatest value (including a negative range)
// In this case the gpx is named: CliftonStraightLineIncreasingLong.gpx

BOOST_AUTO_TEST_CASE( CheckLongFlatHorizLine )
{
   Route route = Route(LogFiles::GPXRoutesDir + "CliftonStraightLineIncreasingLong.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), -1.16021);
}

// A test case to test that the right Longitude is being returned from a GPX file where the gridworld represents a straight vertical line
// The returned Longitude should be the greatest value (including a negative range)
// multiple points along the route will have this same Long
// In this case the gpx is named: CliftonStraightLineIncreasingLong.gpx

BOOST_AUTO_TEST_CASE( CheckLongFlatVertLine )
{
   Route route = Route(LogFiles::GPXRoutesDir + "CliftonStraightVerticalLine.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), -1.19);
}


BOOST_AUTO_TEST_CASE( CheckAcrossPrimeMeridian )
{
   Route route = Route(LogFiles::GPXRoutesDir + "AcrossGreenwichPrimeMeridian.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), 0.0144234);
}

BOOST_AUTO_TEST_CASE( CheckAlongPrimeMeridian )
{
   Route route = Route(LogFiles::GPXRoutesDir + "AlongGreenwichPrimeMeridian.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), 0);
}

BOOST_AUTO_TEST_CASE( ExceedMaxLongitudeWithloop  )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ExceedMaxLongitudeNearUelkal.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), 179.999);
}


BOOST_AUTO_TEST_CASE( AlongMaxLongitude )
{
   Route route = Route(LogFiles::GPXRoutesDir + "AlongMaxLongitudeNearUelkal.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), 180);
}

BOOST_AUTO_TEST_CASE( AcrossMaxLongitudeWithNoLoop )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ExceedMaxLongitudeNearUelkalNoLoop.gpx", isFileName);
   BOOST_CHECK_THROW( route.maxLongitude(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( AcrossMaxLongitudeWithNoLoopBackwards )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ExceedMaxLongitudeNearUelkalNoLoopBackwards.gpx", isFileName);
   BOOST_CHECK_THROW( route.maxLongitude(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( SmallLongChanges )
{
   Route route = Route(LogFiles::GPXRoutesDir + "LongitudeChangeOf0000001.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), -1.0000000);
}

BOOST_AUTO_TEST_CASE( LargeLongChanges )
{
   Route route = Route(LogFiles::GPXRoutesDir + "LongitudeChangeOf50.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), 151);
}








BOOST_AUTO_TEST_SUITE_END()

