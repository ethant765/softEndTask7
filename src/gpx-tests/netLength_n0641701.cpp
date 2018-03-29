/*
        ######## N0641701's Route::netLength() Test File ########

netLength calculates the distance between the first and last points on the Route.

All log files used will be generated with the program that I built to generate log files unless stated otherwise.



All tests catagorised, and they are as follows:



### These are normal tests to check that the function is giving the correct output.

Test: CorrectOutput
Decscription:
This test will test the function for the correct
output given a number of points which have a known
distance between the first and last point.

Test: OnePoint
Description: This test will test the function on
how it handles a route with only one point. The expected
output should be 0, as there is no distance to measure.

Test: TwoPoints
Description: This test will test the function on
how it handles a route with just two points with
a distance. The expected output should be the distance
between the two points.

Test: BackToStart
Description: This test will test the function against
a route that loops back to its starting point. Therefore
the 0 is the expected output.

Test: TwoIdenticalPoints
Description: Two points with the same location. This test
should give a distance of 0.

Test: UpAndDown
Description: This test will present points that do not move
latitudinally or longitudinally but in elevation. The
distance expected is 0. I have manually created the log file for this.



### These tests are designed to catch any errors when it comes to handling positive and negative numbers.

Test: PosLatLong
Description: Testing the function against positive
latitudinal and positive longitudinal points which
shouldn't affect the output.

Test: PosLatNegLong
Description: Testing the function against positive
latitudinal data and negative longitudinal data.

Test: NegLatNegLong
Decscription: Testing the function against negative
longitudinal data and negative longitudinal data.

Test: NegLatPosLong
Description: Testing the function against negative
longitudinal data and positive longitudinal data.



### Edge cases

Test: BigNumbers
Description: Testing the function on how well it can handle large numbers.
I've manually created these log files with very large numbers to see how well
they'll be handled.

Test: SmallNumbers
Description Testing against very small numbers to see if the function
can handle them.

Test: LargeAmountOfData
Description: Testing the function against a large number of points to see if it will handle it.

*/

#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( NetLength )

const bool isFileName = true;

BOOST_AUTO_TEST_CASE(CorrectOutput)
{
    Route route = Route(LogFiles::GPXRoutesDir + "CorrectOutput.gpx", isFileName);

}


