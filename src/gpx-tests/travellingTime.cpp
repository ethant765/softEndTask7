#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Travel_Time )

const bool isFileName = true;

//Checks that the travel time is correct for GPX route containing positions
BOOST_AUTO_TEST_CASE ( correct_travel_time )
{
    Track track = Track(LogFiles::GPXTracksDir + "A1B3C.gpx", isFileName);
    BOOST_CHECK_EQUAL(track.travellingTime(), 40);
}
BOOST_AUTO_TEST_SUITE_END()
