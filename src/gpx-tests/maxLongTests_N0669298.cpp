#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_MaxLongitude_N0669298 )

const bool isFileName = true;

// Edwin Jack Langley
// N0669298

// ==================================================================

// In this file a suite of tests have been define to test the implementation of the route.maxLongitude() method, particularly usages of the
// function where edge cases may be found. An edge case is problem that arrises from minimum / maximum (or close to) parameters that the method
// can handle being used. An example of this in my test suit is testing a Longitude of 180.

// Below is an explanation of each of the test cases and the purpose for testing this data.

// = CheckLongFlatHorizLine =

// A test case to test that the right Longitude is being returned from a GPX file where the gridworld represents a straight line
// The returned Longitude should be the greatest value (including a negative range)
// In this case the gpx is named: CliftonStraightLineIncreasingLong.gpx
// The purpose of this test is to see if the function is capable of sorting the maximum longitude in normal usage.

// = CheckLongFlatVertLine =

// A test case to test that the right Longitude is being returned from a GPX file where the gridworld represents a straight vertical line
// The returned Longitude should be the greatest value (range including a negative range)
// multiple points along the route will have this same Longitude
// In this case the gpx is named: CliftonStraightLineIncreasingLong.gpx
// The purpose of this test is to see if the maximum Longitude can still be drawn from a set of GPX data where there is only 1 Longitude value that reccurs.

// = CheckAcrossPrimeMeridian =

// A test case to test that the right Longitude is being returned from a GPX file where the gridworld represents a straight horizontal line
// In this case the line is crossing the primeMeridian in Greenwich (which is the  point at which Longitude is 0)
// The longitude will pass from being a negative value to a positive one
// In this case the gpx is named: AcrossGreenwichPrimeMeridian.gpx
// The purpose of this test is to see if the implementation can cope when the the Longitude changes from being a negative value to a positive one.
// This could be an error as the function could attempt to take the abs value of the Longitude and could therefore pick a negative one.

// = CheckAlongPrimeMeridian =

// A test case to test that the right Longitude is being returned from a GPX file where the gridworld represents a straight vertical line
// In this case the line is running along the primeMeridian in line with Greenwich (which is the  point at which Longitude is 0)
// The longitude will remain as being 0 through all of the points
// In this case the gpx is named: AlongGreenwichPrimeMeridian.gpx
// The purpose of this test is to see if the implemtation can recognise 0 as a maximum value.

// = ExceedMaxLongitudeWithloop =

// A test case to test that the right Longitude is being returned from a GPX file where the gridworld represents a straight horizontal line
// In this case the line is running across the antimeridian in line with Russia and Fiji (which is the  point at which Longitude is 180)
// The longitude will change from the maximum positive value possible for Longitude to the maximum negative value
// This test assumes that the gpx file was generated using an application that takes the limits of Longitude into consideration
// In this case the gpx is named: ExceedMaxLongitudeNearUelkal.gpx
// The purpose of this test is to see the result when a gpx file has correctly generated with a limit of 180 <= x <= 180 

// = AlongMaxLongitude =

// A test case to test that the right Longitude is being returned from a GPX file where the gridworld represents a straight vertical line
// In this case the line is running along the antimeridian in line with Russia and Fiji (which is the  point at which Longitude is 180)
// The longitude will remain at the maximum positve value ( 180 )
// In this case the gpx is named: AlongMaxLongitudeNearUelkal.gpx
// The purpose of this test is to see if the implemtation can recognise 180 as a maximum value.

// = AcrossMaxLongitudeWithNoLoop =

// A test case to test that the an exception is being thrown from the implementation of MaxLongitude
// In this case the line is running across the antimeridian in line with Russia and Fiji (which is the  point at which Longitude is 180)
// The longitude will change from the maximum positive and continue past its bounds
// This test assumes that the gpx file was generated using an application that does not take the limits of Longitude into consideration
// In this case the gpx is named: ExceedMaxLongitudeNearUelkalNoLoop.gpx
// We should expext this test to throw an out of range error as it passes forwards past this limit

// = AcrossMaxLongitudeWithNoLoopBackwards =

// A test case to test that the an exception is being thrown from the implementation of MaxLongitude
// In this case the line is running across the antimeridian in line with Russia and Fiji (which is the  point at which Longitude is 180)
// The longitude will change from the maximum negative value and continue past its bounds
// This test assumes that the gpx file was generated using an application that does not take the limits of Longitude into consideration
// In this case the gpx is named: ExceedMaxLongitudeNearUelkalNoLoopBackwards.gpx
// We should expext this test to throw an out of range error as it passes backwards past this limit

// = SmallLongChanges =

// A test case to test that the right Longitude is being returned from a GPX file where the gridworld represents a straight vertical line
// In this case the line is running horizontally with only a change of .0000001 Longitude between each point
// In this case the gpx is named: LongitudeChangeOf0000001.gpx
// The purpose of this test is to see if the implementtion can recognise very small changes.

// = LargeLongChanges = 

// A test case to test that the right Longitude is being returned from a GPX file where the gridworld represents a straight vertical line
// In this case the line is running horizontally with a change of 50 Longitude between each point
// In this case the gpx is named: LongitudeChangeOf50.gpx
// The purpose of this test is to see if the implementtion can recognise larger changes.




BOOST_AUTO_TEST_CASE( CheckLongFlatHorizLine )
{
   Route route = Route(LogFiles::GPXRoutesDir + "CliftonStraightLineIncreasingLong.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), -1.16021);
}


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
   BOOST_CHECK_EQUAL( route.maxLongitude(), 1.0000004);
}


BOOST_AUTO_TEST_CASE( LargeLongChanges )
{
   Route route = Route(LogFiles::GPXRoutesDir + "LongitudeChangeOf50.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), 151);
}

BOOST_AUTO_TEST_SUITE_END()

