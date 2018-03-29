#include <boost/test/unit_test.hpp>


#include "geometry.h"
#include "logs.h"
#include "route.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_maxGradient_N0697611 )

const bool isFileName = true;


BOOST_AUTO_TEST_CASE( elev_zero_throughout )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxGradient(), 0 );
}

//BOOST_AUTO_TEST_CASE( NorthYorkMoors)
//{


//Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
//BOOST_CHECK_EQUAL( route.maxGradient(), 0 );
//}


//BOOST_AUTO_TEST_CASE( Route30Positions)
//{


//Route route = Route(LogFiles::GPXRoutesDir + "Route30Positions.gpx", isFileName);
//BOOST_CHECK_EQUAL( route.maxGradient(), 0 );
//}



//BOOST_AUTO_TEST_CASE( N0697611_modified_ABBM)
//{


//Route route = Route(LogFiles::GPXRoutesDir + "N0697611_modified_ABBM.gpx", isFileName);
//BOOST_CHECK_EQUAL( route.maxGradient(), 0 );
//}


//BOOST_AUTO_TEST_CASE( N0697611_OnlyDownhill)
//{


//Route route = Route(LogFiles::GPXRoutesDir + "N0697611_OnlyDownhill.gpx", isFileName);
//BOOST_CHECK_EQUAL( route.maxGradient(), 0 );
//}

BOOST_AUTO_TEST_CASE( N0697611_CHMR)
{


Route route = Route(LogFiles::GPXRoutesDir + "N0697611_CHMR.gpx", isFileName);
BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(20,1000)),0.1) ;
}

BOOST_AUTO_TEST_CASE( N0697611_MRSXY)
{


Route route = Route(LogFiles::GPXRoutesDir + "N0697611_MRSXY.gpx", isFileName);
BOOST_CHECK_EQUAL( route.maxGradient(), 0 );
}

BOOST_AUTO_TEST_CASE( N0697611_MSY_DownhillOnly)
{


Route route = Route(LogFiles::GPXRoutesDir + "N0697611_MSY_DownhillOnly.gpx", isFileName);
BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(-20,1414)),0.1) ;
}

BOOST_AUTO_TEST_CASE( N0697611_MRW_DownhillOnly)
{


Route route = Route(LogFiles::GPXRoutesDir + "N0697611_MRW_DownhillOnly.gpx", isFileName);
BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(-20,1000)),0.1) ;
}

BOOST_AUTO_TEST_CASE( N0697611_MR_Equator_DownhillOnly)
{


Route route = Route(LogFiles::GPXRoutesDir + "N0697611_MR_Equator_DownhillOnly.gpx", isFileName);
BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(-20,1000)),0.1) ;
}

BOOST_AUTO_TEST_CASE( N0697611_MN_Equator_DownhillOnly)
{


Route route = Route(LogFiles::GPXRoutesDir + "N0697611_MN_Equator_DownhillOnly.gpx", isFileName);
BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(-20,1000)),0.1) ;

}

BOOST_AUTO_TEST_CASE( N0697611_HMR_NorthPole)
{


Route route = Route(LogFiles::GPXRoutesDir + "N0697611_HMR_NorthPole.gpx", isFileName);
BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(20,100)),0.1) ;

}

BOOST_AUTO_TEST_CASE( N0697611_MR_NorthPole)
{


Route route = Route(LogFiles::GPXRoutesDir + "N0697611_MR_NorthPole.gpx", isFileName);
BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(-20,100)),0.1) ;

}

BOOST_AUTO_TEST_CASE( N0697611_HR_NorthPole)
{


Route route = Route(LogFiles::GPXRoutesDir + "N0697611_HR_NorthPole.gpx", isFileName);
BOOST_CHECK_EQUAL(route.maxGradient(), 0) ;

}



BOOST_AUTO_TEST_CASE( N0697611_MRX_Pontianak)
{


Route route = Route(LogFiles::GPXRoutesDir + "N0697611_MRX_Pontianak.gpx", isFileName);
BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(-20,100)),0.1) ;

}
BOOST_AUTO_TEST_CASE( N0697611_KLMN_Pontianak)
{


Route route = Route(LogFiles::GPXRoutesDir + "N0697611_KLMN_Pontianak.gpx", isFileName);
BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(1000000,100)),0.1) ;

}
BOOST_AUTO_TEST_SUITE_END()
