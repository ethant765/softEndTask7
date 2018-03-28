//Created by N0689061
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE RouteTests
#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

//check to see if the correct max elevation is being read in from the dataset
BOOST_AUTO_TEST_SUITE( Valid_Max_Elevations )

const bool isFileName = true;

BOOST_AUTO_TEST_CASE(negativeElevation){
    Track track = Track(LogFiles::GPXTracksDir + "negativeElevation.gpx", isFileName);
    BOOST_CHECK_CLOSE(track.maxElevation(), 262, 0.01);
}

BOOST_AUTO_TEST_CASE(positiveElevation){
    Track track = Track(LogFiles::GPXTracksDir + "positiveElevation.gpx", isFileName);
    BOOST_CHECK_CLOSE(track.maxElevation(), 207, 0.01);
}

BOOST_AUTO_TEST_CASE(ZigZag){
    Route route = Route(LogFiles::GPXRoutesDir + "ZigZag.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.maxElevation(), 160, 0.01);
}

BOOST_AUTO_TEST_SUITE_END()



//check to see if the correct min elevation is being read in from the dataset
BOOST_AUTO_TEST_SUITE( Valid_Min_Elevations )

const bool isFileName = true;

BOOST_AUTO_TEST_CASE(negativeElevation){
    Track track = Track(LogFiles::GPXTracksDir + "negativeElevation.gpx", isFileName);
    BOOST_CHECK_CLOSE(track.minElevation(), 27, 0.01);
}

BOOST_AUTO_TEST_CASE(positiveElevation){
    Track track = Track(LogFiles::GPXTracksDir + "positiveElevation.gpx", isFileName);
    BOOST_CHECK_CLOSE(track.minElevation(), 5, 0.01);
}

BOOST_AUTO_TEST_CASE(ZigZag){
    Route route = Route(LogFiles::GPXRoutesDir + "ZigZag.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.minElevation(), 60, 0.01);
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE( Net_Height_Gain )

const bool isFileName = true;

//check to see if 0 is returned when there is no elevation
BOOST_AUTO_TEST_CASE(No_elevation){
    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.minElevation(), 0, 0.01);
}

//check to see if the answer is 0 with only negative elevations, and to see if a negative elevation result returns 0
BOOST_AUTO_TEST_CASE(negative_elevations){
    Track track = Track(LogFiles::GPXTracksDir + "negativeElevation.gpx", isFileName);
    BOOST_CHECK_CLOSE(track.netHeightGain(), 0, 0.01);
}

//check to see if the answer is correct even when there is a large dataset
BOOST_AUTO_TEST_CASE(large_dataset){
    Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.netHeightGain(), 0, 0.01);
}

//check to see if the answer is correct with only positive elevations
BOOST_AUTO_TEST_CASE(positive_elevations){
    Track track = Track(LogFiles::GPXTracksDir + "positiveElevation.gpx", isFileName);
    BOOST_CHECK_CLOSE(track.netHeightGain(), 202, 0.01);
}

//check to see if the answer is correct with alternating positive and negative elevations are being read in
BOOST_AUTO_TEST_CASE(alternating_elevations){
    Route route = Route(LogFiles::GPXRoutesDir + "ZigZag.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.netHeightGain(), 50, 0.01);
}

//Test to see if the answer is correct with a single value
BOOST_AUTO_TEST_CASE(single_elevation){
    Route route = Route(LogFiles::GPXRoutesDir + "Edge.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.netHeightGain(), 0, 0.01);
}

BOOST_AUTO_TEST_SUITE_END()
