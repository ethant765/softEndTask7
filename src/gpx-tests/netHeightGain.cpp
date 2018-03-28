//Created by N0689061
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE RouteTests
#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Valid_Max_Elev )

const bool isFileName = true;

//check to see if the correct max elevation is being read in
BOOST_AUTO_TEST_CASE(ABCD_max_elev){
    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.maxElevation(), 0);
}

//check to see if the correct min elevation is being read in
BOOST_AUTO_TEST_CASE(valid_last_value){
    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.minElevation(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( Net_Height_Gain )

const bool isFileName = true;

//check to see if the correct max elevation is being read in
BOOST_AUTO_TEST_CASE(valid_first_value){
    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.maxElevation(), 0);
}

//check to see if the correct min elevation is being read in
BOOST_AUTO_TEST_CASE(valid_last_value){
    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.minElevation(), 0);
}

////check to see if negative result returns 0
//BOOST_AUTO_TEST_CASE(negative_result){
//    Route route = Route(LogFiles::GPXRoutesDir + "negativeElevation.gpx", isFileName);
//    BOOST_CHECK_EQUAL(route.netHeightGain(), 0);
//}

//check to see if the correct answer for NorthYorkMoors is returned
BOOST_AUTO_TEST_CASE(correct_answer){
    Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.netHeightGain(), 0);
}

//BOOST_AUTO_TEST_CASE(positive_answer){
//    Route route = Route(LogFiles::GPXRoutesDir + "positiveElevation.gpx", isFileName);
//    BOOST_CHECK_EQUAL(route.netHeightGain(), 0);
//}

BOOST_AUTO_TEST_SUITE_END()
