#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Track_TravellingTime )

const bool isFileName = true;

//This checks the travel time is correct when the time duration is set to 10 seconds
//with route A1B2C
BOOST_AUTO_TEST_CASE ( duration_1_sec )
{
    Track track = Track(LogFile::GPXTracksDir + "TrackDuration1", isFileName);
    BOOST_CHECK_EQUAL(track.travellingTime(), 3)
}

//This checks the travel time is correct when the time duration is set to 10 seconds
//with route A3B1C
BOOST_AUTO_TEST_CASE ( duration_10_sec )
{
    Track track = Track(LogFile::GPXTracksDir + "TrackDuration10", isFileName);
    BOOST_CHECK_EQUAL(track.travellingTime(), 40)
}

//this checks the travel time is correct when the time duration is set to an even number, 2 in this case
//with route A4B2C
BOOST_AUTO_TEST_CASE( duration_2_sec)
{
    Track track = Track(LogFile::GPXTracksDir + "TrackDurationEven", isFileName);
    BOOST_CHECK_EQUAL(track.travellingTime(), 12)
}

//this checks the travel time is correct when the time duration is set to an odd number, 7 in this case
//with route M3A2G
BOOST_AUTO_TEST_CASE ( duration_7_sec)
{
    Track track = Track(LogFile::GPXTracksDir + "TrackDurationOdd", isFileName);
    BOOST_CHECK_EQUAL(track.travellingTime(), 35)
}

BOOST_AUTO_TEST_SUITE_END()
