#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_minGradient )

const bool isFileName = true;

// Check that the minGradient is correct for a GPX route containing a <name> element within <rte>.
BOOST_AUTO_TEST_CASE( routABCD )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minGradient(), 0 );
}


BOOST_AUTO_TEST_SUITE_END()
