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
8. test for max elevation from a list of elevation values with no specific ordering (eg. low, low , high, high, high, etc).
9. test for max elevation from a list of assending elevation values.
10. test for max elevation from a list of desending elevation values.

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

// Test to see if correct max elevation is returned from only a positive dataset 
BOOST_AUTO_TEST_CASE( positive_max_elevation ) {
    Route route = Route(LogFiles::GPXRoutesDir + "positive_elevation_n0689529.gpx", isFileName);
    BOOST_CHECK_CLOSE( route.maxElevation(), 20.000000, 0.001);
}

// Test to see if correct max elevation is returned from only a negative dataset
BOOST_AUTO_TEST_CASE( negative_max_elevation ) {
    Route route = Route(LogFiles::GPXRoutesDir + "negative_elevation_n0689529.gpx", isFileName);
    BOOST_CHECK_CLOSE( route.maxElevation(), -5.000000, 0.001);
}

/*
// Test to see if correct max elevation is returned from a dataset containing 
// both positive and negative elevation values 
BOOST_AUTO_TEST_CASE( max_elevation_pos_neg_dataset ) {
    Route route = Route(LogFiles::GPXRouteDir + "", isFileName);
    BOOST_CHECK_EQUAL( route.maxElevation(), "");
}

// Tests for multiples of the same max elevation occuring:

// Test to see if correct max elevation is returned when there are multiple occurences 
// of the max elevation at difference recorded points within the dataset
BOOST_AUTO_TEST_CASE( multiple_max_elevation_instances ) {
    Route route = Route(LogFiles::GPXRouteDir + "", isFileName);
    BOOST_CHECK_EQUAL( route.maxElevation(), "");
}

// Test to see if max elevation is returned from a dataset where all elevation 
// values are the same ie. the recoreded area is flat
BOOST_AUTO_TEST_CASE( flat_elevation ) {
    Route route = Route(LogFiles::GPXRouteDir + "", isFileName);
    BOOST_CHECK_EQUAL( route.maxElevation(), "");
} 

// Tests for max elevation from a dataset that follows a specific pattern

// Test to see if max elevation is returned from a dataset with 
// alternating elevation values of high to low.
BOOST_AUTO_TEST_CASE( max_elevation_alternating_high_low ) {
    Route route = Route(LogFiles::GPXRouteDir + "", isFileName);
    BOOST_CHECK_EQUAL( route.maxElevation(), "");
}

// Test to see if mac elevation is returned from a dataset with
// alternating elevation values low to high
BOOST_AUTO_TEST_CASE( max_elevation_alternating_low_high ) {
    Route route = Route(LogFiles::GPXRouteDir + "", isFileName);
    BOOST_CHECK_EQUAL( route.maxElevation(), "");
}

// Test to see if max elevation is returned from a dataset with random 
// alternation of its elevation values 
BOOST_AUTO_TEST_CASE( max_elevation_random_alternation ) {
    Route route = Route(LogFiles::GPXRouteDir + "", isFileName);
    BOOST_CHECK_EQUAL( route.maxElevation(), "");
}

// Test to see if max elevation is returned form a assending dataset
BOOST_AUTO_TEST_CASE( max_elevation_assending ) {
    Route route = Route(LogFiles::GPXRouteDir + "", isFileName);
    BOOST_CHECK_EQUAL( route.maxElevation(), "");
}

// Test to see if max elevation is returned from a desending dataset
BOOST_AUTO_TEST_CASE( max_elevation_desending ) {
    Route route = Route(LogFiles::GPXRouteDir + "", isFileName);
    BOOST_CHECK_EQUAL( route.maxElevation(), "");
}
*/
BOOST_AUTO_TEST_SUITE_END()

