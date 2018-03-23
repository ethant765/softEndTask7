#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_MaxLat )

const bool isFileName = true;

// Checking that the MaxLatitude function can find the highest Latitude within the ABCD.gpx given route log
BOOST_AUTO_TEST_CASE( RouteABCD )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLatitude(), 0.179964);
}

// Checking that the MaxLatitude function can find the highest Latitude within the A1B3C.gpx given track log
BOOST_AUTO_TEST_CASE( TrackA1B3C )
{
   Track track = Track(LogFiles::GPXTracksDir + "A1B3C.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.maxLatitude(), 0.179964);
}

// Checking that the MaxLatitude function can find the highest Latitude within the NorthYorkMoors.gpx given route log.
BOOST_AUTO_TEST_CASE( RouteNorthYorkMoors )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLatitude(), 54.50918734073639);
}


//MY TESTS

// Checking that the MaxLatitude function can find the highest Latitude within the RouteStationaryPoints.gpx route log.
//This Route contains 5 points, all containing the same Latitude, this will test that the function MaxLatitude will be able
//to get the highest latitude out of the points
BOOST_AUTO_TEST_CASE( RouteStationaryPoints )
{
   Route route = Route(LogFiles::GPXRoutesDir + "RouteStationaryPoints.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLatitude(), 53.1381);
}

// Checking that the MaxLatitude function can find the highest Latitude within the TrackStationaryPoints.gpx given Track log.
//This Track contains 5 points, all containing the same Latitude, this will test that the function MaxLatitude will be able
//to get the highest latitude out of the points
BOOST_AUTO_TEST_CASE( TrackStationaryPoints )
{
   Track track = Track(LogFiles::GPXTracksDir + "TrackStationaryPoints.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.maxLatitude(), 0.179964);
}

//Checking function can handle negative numbers with stationary points in a Route
BOOST_AUTO_TEST_CASE( RouteStationaryNegativePoints )
{
   Route route = Route(LogFiles::GPXRoutesDir + "RouteStationaryNegativePoints.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLatitude(), -29.82);
}
//Checking the MaxLatitude function can handle negative numbers with stationary points in a Track file
BOOST_AUTO_TEST_CASE( TrackStationaryNegativePoints )
{
   Track track = Track(LogFiles::GPXTracksDir + "TrackStationaryNegativePoints.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.maxLatitude(), -24.82);
}


//This test checks that the function can still get the correct MaxLattiude from a route with points that increase in longitude, but latitude stay the same
BOOST_AUTO_TEST_CASE( RouteChangingLongitude )
{
   Route route = Route(LogFiles::GPXRoutesDir + "RouteChangingLongitude.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLatitude(), 53.1381);
}

//This test checks that the function can still get the correct MaxLattiude from a track with points that increase in longitude, but latitude stay the same
BOOST_AUTO_TEST_CASE( TrackChangingLongitude )
{
   Track track = Track(LogFiles::GPXTracksDir + "TrackChangingLongitude.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.maxLatitude(), 0.179964);
}

//This test checks if the function MaxLat can find the maximum latitude when Route has points with negative latitude, and changing negative longitude
BOOST_AUTO_TEST_CASE( RouteNegativeChangingLongitude )
{
   Route route = Route(LogFiles::GPXRoutesDir + "RouteNegativeChangingLongitude.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLatitude(), -11.32);
}

//This test checks that the function can still get the correct MaxLattiude from a track with points that increase in longitude, but latitude stay the same
BOOST_AUTO_TEST_CASE( TrackNegativeChangingLongitude )
{
   Track track = Track(LogFiles::GPXTracksDir + "TrackNegativeChangingLongitude.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.maxLatitude(), -44.82);
}

//To see if MaxLatitude can find the correct maximum latitude when the first point has the highest latitude, and then all points after decrease in latitude
BOOST_AUTO_TEST_CASE ( RouteLatiudeDecreases )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteLatiudeDecreases.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 51.68);
}

//Test if MaxLatitude gets the correct highest latitude on a track when all the points of latitude decrease
BOOST_AUTO_TEST_CASE ( TrackLatiudeDecreases )
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackLatiudeDecreases.gpx", isFileName);
    BOOST_CHECK_EQUAL( track.maxLatitude(), 75.18 );
}

//Route file with a Negative Latitude that decreases
BOOST_AUTO_TEST_CASE ( RouteNegativeLatiudeDecreases )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteNegativeLatiudeDecreases.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), -34.82);
}

//Track with a negative latitude that decreases throughout the track
BOOST_AUTO_TEST_CASE ( TrackNegativeLatiudeDecreases )
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackNegativeLatiudeDecreases.gpx", isFileName);
    BOOST_CHECK_EQUAL( track.maxLatitude(), -50.82 );
}

//Route file with a Latitude that increases
BOOST_AUTO_TEST_CASE ( RouteLatitudeIncreases )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteLatiudeIncreases.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 65.18 );
}

//Track  with latitude that increases throughout the track
BOOST_AUTO_TEST_CASE ( TrackLatitudeIncreases )
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackLatiudeIncreases.gpx", isFileName);
    BOOST_CHECK_EQUAL( track.maxLatitude(), 41.18);
}


//Route file with a negativev Latitude that increases
BOOST_AUTO_TEST_CASE ( RouteNegativeLatiudeIncreases )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteNegativeLatiudeIncreases.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), -41.94 );
}

//Track  with  negative latitude that increases throughout the track
BOOST_AUTO_TEST_CASE ( TrackNegativeLatiudeIncreases )
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackNegativeLatiudeIncreases.gpx", isFileName);
    BOOST_CHECK_EQUAL( track.maxLatitude(), -31.17);
}



//Route log  with latitude decreasing and then increasing
BOOST_AUTO_TEST_CASE ( RouteLatDecreaseThenIncrease )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteLatDecreaseThenIncrease.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 24.46 );
}

//Track with latitude decreases and then increases
BOOST_AUTO_TEST_CASE ( TrackLatDecreaseThenIncrease )
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackLatDecreaseThenIncrease.gpx", isFileName);
    BOOST_CHECK_EQUAL( track.maxLatitude(), 27.93);
}



//Route log with Increasing latitude then decreasing
BOOST_AUTO_TEST_CASE ( RouteLatIncreaseThenDecrease )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteLatIncreaseThenDecrease.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 35.18 );
}



//Track  with latitude increasing then decreasing
BOOST_AUTO_TEST_CASE ( TrackLatIncreaseThenDecrease )
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackLatIncreaseThenDecrease.gpx", isFileName);
    BOOST_CHECK_EQUAL( track.maxLatitude(), 11.31);
}


//Route With Latitude of 89.9 testing edge cases. As lat can only be between -90 and 90
BOOST_AUTO_TEST_CASE ( RouteLatAt89 )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteLatAt89.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 89.9818 );
}

//Track with latitude at 89.9 testing the edge cases 
BOOST_AUTO_TEST_CASE ( TrackLatAt89 )
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackLatAt89.gpx", isFileName);
    BOOST_CHECK_EQUAL( track.maxLatitude(), 89.9818);
}

    

//Testing the other edge case of -89 in a route log to see if the function can handle this number
BOOST_AUTO_TEST_CASE ( RouteLatAtNegative89 )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteLatAtNegative89.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), -62.8436 );
}

//Testing if the MaxLat function works properly with the edge case -89 within the Track log 
BOOST_AUTO_TEST_CASE ( TrackLatAtNegative89 )
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackLatAtNegative89.gpx", isFileName);
    BOOST_CHECK_EQUAL( track.maxLatitude(), -62.8436);
}


//Test case to see if the Maximum latitude was able to be identified in a Route log with only 1 position
BOOST_AUTO_TEST_CASE ( RouteSinglePosition )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteSinglePosition.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 42.74 );
}

//Test case to see if MaximumLatitude can find the correct value of lattitude when there is 30 different points within the route log
BOOST_AUTO_TEST_CASE ( Route30Positions )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Route30Positions.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 60.7364 );
}

//Test case to check if Latitude greater than 90 can be accepted
BOOST_AUTO_TEST_CASE ( RouteLatitudeGreater90 )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteLatitudeGreater90.gpx", isFileName);
    BOOST_CHECK_THROW( route.maxLatitude(), std::out_of_range);
}

//Test case to check if Latitude smaller than -90 can be accepted
BOOST_AUTO_TEST_CASE ( RouteLatitudeSmaller90 )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteLatitudeSmaller90.gpx", isFileName);
    BOOST_CHECK_THROW( route.maxLatitude(), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()

