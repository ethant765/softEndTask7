/*
Author: Callum Roberts - N0689529

///////////////////////////////////////////////////////////////////////////////////////////
Unit test for - metres Route::maxElevation() const

Design:
------- 
Max elevation has the possiablity of being either POSITIVE or NEGATIVE:
1. test for max elevation from a list of positve elevation values. 
2. test for max elevation from a list of negative elevation values.
3. test for max elevation from a list of both positve and negative elevation values.

The value of the max elevation could occure multiple time in the same set of data:
4. test for max elevation where the max value occurs multiple times from a list of elevation values.
5. test where the max elevation is constant ie. all the elevation values in the list are the same.

The values in the list of elevations could be staggerd or ordered in a specific way, hence test different list patterns:
6. test for max elevation from a list of alterneting elevation values (high to low, high to low, etc).
7. test for max elevation from a list of alternating elevation values (low to high, low to high, etc).
8. test for max elevation from a list of randomly alternating elevation values (eg. low, low , high, high, high, etc).
9. test for max elevation from a list of assending elevation values.
10. test for max elevation from a list of desending elevation values.

Other tests if time:
11. if a known altitude at a specific coordinate is known to be X, but is found to be equal to Y then the test should fail.
12. formatting tests.

cases I did consider, but deemed unnecessary:
A. The maximum altitude on earth is Mt. Everest, so I could have potentially tested to see if a elevation exceeded this.
	if true then it could be incorrect, however if the data was recorded from a plane then this max alt could be exceeded.


///////////////////////////////////////////////////////////////////////////////////////////
*/

#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;


BOOST_AUTO_TEST_SUITE( max_elevation )

const bool isFileName = true;

// Tests for positive or negative max elevations:

// Test: 1. (test number referenced with design section) 
BOOST_AUTO_TEST_CASE( max_elevation_from_positve_list ) {
    Route route = Route(LogFiles::GPXRoutesDir + "", isFileName);
    
}

// Test: 2.
BOOST_AUTO_TEST_CASE( max_elevation_from_negative_list ) {

}

// Test: 3.
BOOST_AUTO_TEST_CASE( max_elevation_form_pos_neg_list ) {

}




//BOOST_AUTO_TEST_SUITE( Route_name )

//const bool isFileName = true;

// Check that the name is correct for a GPX route containing a <name> element within <rte>.
//BOOST_AUTO_TEST_CASE( name_present_route )
//{
//   Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
//   BOOST_CHECK_EQUAL( route.name(), "ABCD" );
//}

// Check that the name is correct for a GPX track containing a <name> element within <trk>.
//BOOST_AUTO_TEST_CASE( name_present_track )
//{
//   Track track = Track(LogFiles::GPXTracksDir + "A1B3C.gpx", isFileName);
//   BOOST_CHECK_EQUAL( track.name(), "A1B3C" );
//}

// Check that the name is correct for a GPX route without a <name> element within <rte>.
//BOOST_AUTO_TEST_CASE( name_absent )
//{
//   Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
//   BOOST_CHECK_EQUAL( route.name(), "Unnamed Route" );
//}

//BOOST_AUTO_TEST_SUITE_END()
