//Created by N0689061
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE RouteTests
#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

//check for edge case - only one point
//check for zig zag route
//check for a high number of points
//positive elev only
//negative elev only
//no evev
//difference between route and track data

BOOST_AUTO_TEST_SUITE( Valid_Max_Elev )

const bool isFileName = true;

//check to see if the correct max elevation is being read in
BOOST_AUTO_TEST_CASE(ABCD_max_elev){
    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.maxElevation(), 0, 0.1);
}

//check to see if the correct max elevation is being read in
BOOST_AUTO_TEST_CASE(NYM_max_elev){
    Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.maxElevation(), 505, 0.1);
}

BOOST_AUTO_TEST_CASE(NE_max_elev){
    Track track = Track(LogFiles::GPXTracksDir + "negativeElevation.gpx", isFileName);
    BOOST_CHECK_CLOSE(track.maxElevation(), 505, 0.1);
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE( Net_Height_Gain )

const bool isFileName = true;

//check to see if the correct max elevation is being read in
BOOST_AUTO_TEST_CASE(valid_first_value){
    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.maxElevation(), 0, 0.1);
}

//check to see if the correct min elevation is being read in
BOOST_AUTO_TEST_CASE(valid_last_value){
    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.minElevation(), 0, 0.1);
}

//check to see if negative result returns 0
BOOST_AUTO_TEST_CASE(negative_result){
    Track track = Track(LogFiles::GPXTracksDir + "negativeElevation.gpx", isFileName);
    BOOST_CHECK_EQUAL(track.netHeightGain(), 0);
}

//check to see if the correct answer for NorthYorkMoors is returned
BOOST_AUTO_TEST_CASE(correct_answer){
    Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.netHeightGain(), 0, 0);
}

BOOST_AUTO_TEST_CASE(positive_answer){
    Track track = Track(LogFiles::GPXTracksDir + "positiveElevation.gpx", isFileName);
    BOOST_CHECK_EQUAL(track.netHeightGain(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
