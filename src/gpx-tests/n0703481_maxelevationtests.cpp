#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"

using namespace GPS;


BOOST_AUTO_TEST_SUITE( maxElevation_N0703481)

const bool isFileName = true;


BOOST_AUTO_TEST_CASE( PositiveToNegativeElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0703481_pos_to_neg_ele.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), 70 );
}


BOOST_AUTO_TEST_CASE( NegativeToPositiveElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0703481_neg_to_pos_ele.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), 200 );
}


BOOST_AUTO_TEST_CASE( NegativeToPositiveToNegativeElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0703481_neg_to_pos_to_neg_ele.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), 30 );
}


BOOST_AUTO_TEST_CASE( PositiveToNegativeToPositiveElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0703481_pos_to_neg_to_pos_ele.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), 50 );
}


BOOST_AUTO_TEST_CASE( OnePosition )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0703481_one_pos.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), 120 );
}


BOOST_AUTO_TEST_CASE( NoPositions )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0703481_no_pos.gpx", isFileName);
   BOOST_CHECK_THROW( route.maxElevation(), std::invalid_argument );
}


BOOST_AUTO_TEST_CASE( SameElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0703481_same_ele.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), 80 );
}


BOOST_AUTO_TEST_CASE( DecreasingNegativeElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0703481_decreasing_neg_ele.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), -10 );
}


BOOST_AUTO_TEST_CASE( LargeRouteFile )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0703481_large_route.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), 5 );
}


BOOST_AUTO_TEST_CASE( SmallIncrementationFile )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0703481_small_incrementation.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), 5 );
}


BOOST_AUTO_TEST_CASE( LargeIncrementationFile )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0703481_large_incrementation.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), 1900 );
}

BOOST_AUTO_TEST_SUITE_END()
