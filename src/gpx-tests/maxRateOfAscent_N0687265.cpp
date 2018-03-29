#include <boost/test/unit_test.hpp>
#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_MaxLongitude_N0669298 )
	
	const bool FileName = true;

	BOOST_AUTO_TEST_CASE( NormalValues ){
		Track track = Track(LogFiles::GPXTracksDir + "N0687265_NormalValues.gpx", FileName);
		BOOST_CHECK_EQUAL( track.maxRateOfAscent() , 20);
	}

	BOOST_AUTO_TEST_CASE( LargeElevationValues ){
		Track track = Track(LogFiles::GPXTracksDir + "N0687265_LargeElevationValues.gpx", FileName);
		BOOST_CHECK_EQUAL( track.maxRateOfAscent() , 200);
	}

	BOOST_AUTO_TEST_CASE( SmallElevationValues ){
		Track track = Track(LogFiles::GPXTracksDir + "N0687265_SmallElevationValues.gpx", FileName);
		BOOST_CHECK_CLOSE( track.maxRateOfAscent() , 0.02, 1);
	}

	BOOST_AUTO_TEST_CASE( DescendingElevationValues ){
		Track track = Track(LogFiles::GPXTracksDir + "N0687265_DescendingElevationValues.gpx", FileName);
		BOOST_CHECK_EQUAL( track.maxRateOfAscent() , 0);
	}

	BOOST_AUTO_TEST_CASE( NoElevationValues ){
		Track track = Track(LogFiles::GPXTracksDir + "N0687265_NoElevationValues.gpx", FileName);
		BOOST_CHECK_EQUAL( track.maxRateOfAscent() , 0);
	}

	BOOST_AUTO_TEST_CASE( LongTimeValues ){
		Track track = Track(LogFiles::GPXTracksDir + "N0687265_LongTimeValues.gpx", FileName);
		BOOST_CHECK_CLOSE( track.maxRateOfAscent() , 0.667, 1);
	}

	BOOST_AUTO_TEST_CASE( ShortTimeValues ){
		Track track = Track(LogFiles::GPXTracksDir + "N0687265_ShortTimeValues.gpx", FileName);
		BOOST_CHECK_EQUAL( track.maxRateOfAscent() , 200);
	}

	BOOST_AUTO_TEST_CASE( ZeroTimeValues ){
		Track track = Track(LogFiles::GPXTracksDir + "N0687265_ZeroTimeValues.gpx", FileName);
		BOOST_CHECK_THROW( track.maxRateOfAscent() , std::overflow_error);
	}

BOOST_AUTO_TEST_SUITE_END()