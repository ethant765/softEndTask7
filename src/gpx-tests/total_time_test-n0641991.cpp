#define BOOST_Test_Module totaltimetest
#include <boost/test/included/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"
#include "types.h"

BOOST_AUTO_TEST_SUITE( totalTimeTest )

//const bool isFileName = true;
//totalTime() == restingTime() + travellingTime()


//Check for invalid values

BOOST_AUTO_TEST_CASE( totalTime_validvalue_restingTime_test )
{
    GPS::seconds restingTime = 2; //meant to represent restingTime() result
    BOOST_REQUIRE_MESSAGE (restingTime < 0, "restingTime() invalid (negative) value"); //Gives message explaining error
}

BOOST_AUTO_TEST_CASE(totalTime_validvalue_travellingTime_test )
{
    GPS::seconds travellingTime = 5; //meant to represent travellingTime() result
    BOOST_REQUIRE_MESSAGE (travellingTime <= 0, "travellingTime at invalid value (less than or equal to 0)");
}

BOOST_AUTO_TEST_CASE( addition_test )
{
    GPS::seconds totalTime; //initating variable for maths test can be replaced by a completed function
    restingTime + travellingTime = totalTime; //what should really be the function
    BOOST_REQUIRE_MESSAGE (totalTime <= 0, "travellingTime at invalid value (less than or equal to 0)");
}

BOOST_AUTO_TEST_SUITE_END()


