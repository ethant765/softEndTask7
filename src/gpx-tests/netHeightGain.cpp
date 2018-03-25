#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE RouteTests
#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Net_Height_Gain )

const bool isFileName = true;

//check that
BOOST_AUTO_TEST_CASE(valid_first_value){
    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.maxElevation(), 0);
}

BOOST_AUTO_TEST_CASE(valid_last_value){
    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.minElevation(), 0);
}

BOOST_AUTO_TEST_CASE(negative_result){

}

BOOST_AUTO_TEST_CASE(correct_answer){

}

BOOST_AUTO_TEST_SUITE_END()
