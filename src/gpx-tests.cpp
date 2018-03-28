#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GPXTests
#include <boost/test/unit_test.hpp>

#include <stdexcept>

#include "xmlparser.h"
#include "logs.h"
#include "route.h"

using namespce GPS;

BOOST_AUTO_TEST_SUITE(MinimumLatitudeTests)

BOOST_AUTO_TEST_CASE(CheckSingleValue)
{
    Route = (LogFiles::GPXRoutesDir +  "singleValueN0682255.gpx", true);



    Route route = Route(filePath, isFileName);
    BOOST_CHECK_EQUAL(Route::minLatitude() , degrees 10)
}

BOOST_AUTO_TEST_SUITE_END()


