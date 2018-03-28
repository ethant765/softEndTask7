#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GPXTests
#include <boost/test/unit_test.hpp>

#include <stdexcept>

#include "xmlparser.h"
#include "logs.h"
#include "route.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE(MinimumLatitudeTests)

BOOST_AUTO_TEST_CASE(CheckSingleValue)
{
    const bool isFileName = true;
    const std::string filePath = LogFiles::GPXRoutesDir + "singleValueN0682255.XML";

    Route route = Route(filePath, isFileName);

    BOOST_CHECK_EQUAL(route.minLatitude() , 0);

}

BOOST_AUTO_TEST_SUITE_END()


