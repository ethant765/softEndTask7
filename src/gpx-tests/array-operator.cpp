/**
 **** Unit tests for the method Route::operator[]()
 *
 * Route::operator[]() returns the Position at the specified index which
 * represents a certain point on the route.
 *
 * First, we should test if Route::operator[]() behaves correctly when the
 * given index refers to a Position within the Route.
 * To do this, we use a GPX file of a route generated using the GridWorld class
 * and we check that the [] operator returns the correct Position at each
 * index.
 *
 * Route::operator[]() should throw an std::out_of_range exception if the index
 * is out of bounds. We should test that the function throws that exception
 * when given an index which is outside the expected interval (from 0 to the
 * size of the route - 1).
 * We also test that an std::out_of_range exception is thrown when the index
 * is negative.
 * We also test the function for edge cases, for example the first and the last
 * Position of the route which should not throw an exception. In addition, we
 * also test the outer bounds of the array (-1 and the route size).
 *
 * Finally, We test Route::operator[]() using an empty route which does not
 * have any points. Since a route contains an array of Positions, the []
 * operator should throw an std::out_of_range exception at any index.
 **/

#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"
#include "position.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_array_operator )

/**
 * Check that Route::operator[] returns all positions of a Route correctly
 * The test Route is extracted from a GPX file generated using the GridWorld
 * class. Thus all the Position values are known.
 * Since Position does not include the == operator, its attributes are checked
 * individually.
 **/
BOOST_AUTO_TEST_CASE( correct_index_route ) {
    Route route = Route(LogFiles::GPXRoutesDir + "MIOT.gpx", true);

    Position pos0 = Position(0, 109.322, 0);
    BOOST_CHECK_EQUAL(route[0].latitude(), pos0.latitude());
    BOOST_CHECK_EQUAL(route[0].longitude(), pos0.longitude());
    BOOST_CHECK_EQUAL(route[0].elevation(), pos0.elevation());

    Position pos1 = Position(0.089982, 109.412, 0);
    BOOST_CHECK_EQUAL(route[1].latitude(), pos1.latitude());
    BOOST_CHECK_EQUAL(route[1].longitude(), pos1.longitude());
    BOOST_CHECK_EQUAL(route[1].elevation(), pos1.elevation());

    Position pos2 = Position(0, 109.502, 0);
    BOOST_CHECK_EQUAL(route[2].latitude(), pos2.latitude());
    BOOST_CHECK_EQUAL(route[2].longitude(), pos2.longitude());
    BOOST_CHECK_EQUAL(route[2].elevation(), pos2.elevation());

    Position pos3 = Position(-0.089982, 109.502, 0);
    BOOST_CHECK_EQUAL(route[3].latitude(), pos3.latitude());
    BOOST_CHECK_EQUAL(route[3].longitude(), pos3.longitude());
    BOOST_CHECK_EQUAL(route[3].elevation(), pos3.elevation());
}

/**
 * Check that operator[] returns all positions of a Track correctly
 * The test Track is extracted from a GPX file generated using the GridWorld
 * class. Thus all the Position values are known.
 * Since Position does not include the == operator, its attributes are checked
 * individually.
 **/
BOOST_AUTO_TEST_CASE( correct_index_track ) {
    Track track = Track(LogFiles::GPXTracksDir + "M3I6O1T.gpx", true);

    Position pos0 = Position(0, 109.322, 0);
    BOOST_CHECK_EQUAL(track[0].latitude(), pos0.latitude());
    BOOST_CHECK_EQUAL(track[0].longitude(), pos0.longitude());
    BOOST_CHECK_EQUAL(track[0].elevation(), pos0.elevation());

    Position pos1 = Position(0.089982, 109.412, 0);
    BOOST_CHECK_EQUAL(track[1].latitude(), pos1.latitude());
    BOOST_CHECK_EQUAL(track[1].longitude(), pos1.longitude());
    BOOST_CHECK_EQUAL(track[1].elevation(), pos1.elevation());

    Position pos2 = Position(0, 109.502, 0);
    BOOST_CHECK_EQUAL(track[2].latitude(), pos2.latitude());
    BOOST_CHECK_EQUAL(track[2].longitude(), pos2.longitude());
    BOOST_CHECK_EQUAL(track[2].elevation(), pos2.elevation());
}

BOOST_AUTO_TEST_SUITE_END()
