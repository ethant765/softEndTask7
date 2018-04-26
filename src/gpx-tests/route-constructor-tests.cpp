#include <boost/test/unit_test.hpp>

#include "route.h"
#include "track.h"
#include "logs.h"

#include <stdexcept>

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_constructor_tests )

bool isFileName = true;

BOOST_AUTO_TEST_CASE(Throw_Domain_Error)
{
    BOOST_CHECK_THROW(Route(LogFiles::GPXRoutesDir + "TestBrokenFile.gpx", isFileName), std::domain_error);
}

BOOST_AUTO_TEST_CASE(Throw_Invalid_Argument_Error)
{
    BOOST_CHECK_THROW(Route(LogFiles::GPXRoutesDir + "sdgfgrsdgrgfgfr.gpx", isFileName), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
