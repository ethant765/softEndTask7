#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"	

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_name )

const bool isFileName = true;

/*
	Function: Total Time
	
	Returns the difference in seconds between the earliest and latest points.
	gridworld_track uses a timeUnitDuration variable, but I don't think it applies to regular Track calculations, so we'll do these functions in terms of GPX time units.
	
	
	Tests/Considerations & Explanations:
	
	CORRECT: 
	
		Regular input:
		Testing correct input ensures the function works as expected.
		
		Regular input, non-zero starting value:
		Ensures the Total Time function isn't assuming the start time is zero
		
		
		
		Correct input, data not ordered correctly by time:
		Though there are arguments for data that isn't ordered being invalid, providing functionality for time going back and forth will help in the case of 
		manually-typed data being slightly incorrect.
		
		The multiple cases for this test I'll cover are:
			Time going backwards
			Latest time out of place (Not first nor last)
			Smallest time out of place (Not first nor last)
			Smallest time immediately before largest time
			Smallest time immediately after largest time
			
		
		
		Correct input, maximum values for time:
		Maximum time unit given that time is ULL = 18446744073709551615		
		This ensures that the function won't fail given large input values (which could cause errors if the function doesn't allocate a large enough variable)
		
		Correct input, minimum values for inputs (No time taken):
		This test can catch issues with handlng small numbers, such as DIV/0 exceptions
		
		Correct input, large quantity of points:
		Choosing a quantity of points to test is a little difficult, as file size and runtime length may become unacceptably large after a few thousand points. 
		Should this program frequently need to track hundreds of thousands of points, this test should be scaled accordingly.
		For the sake of the other students having to download any file, I'll keep this to using 'TrackMultiplePoints'.
		
		
		
	INCORRECT:
		
		After considering the many ways to incorrectly input time values into the GPX files, a lot of the errors will throw exceptions either at parsing time or 
		be completely undetectable for the function itself.
		
		
		
	CONSIDERATIONS & REASONS FOR NOT IMPLEMENTING:
		

		Malformatted XML:
		This error would instead be handled by the parser.
		
		Empty track containing no points:
		If there are no points for the track, the parser will throw an error.
		
		
		Negative time values:
		This error is impossible to be detected by the function itself; negative values wouldn't be handled by the XML parser, which through using stull results in an
		integer value with the first bit flipped, exactly the same as a very large positive value.
			
		Wrong type for time:
		Incorrect types would throw an error at 'StringToTime' and would not reach this function.
		
		Incorrect & Correct input, multiple track segments
		The transformation from XML to Route or Track combines all track segments into a single set of data.
		
		Incorrect values for variables other than 'Time'
		Given the functions' purpose doesn't utilise any variables other than 'Time' in the given track, 
		
*/


// Tests for correct, ordered values
BOOST_AUTO_TEST_CASE( totaltime_correct_set1)
{
   Route route = Route(LogFiles::GPXTracksDir + "TrackDuration10.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.name(), 40 );	
}
BOOST_AUTO_TEST_CASE( totaltime_correct_set1)
{
   Route route = Route(LogFiles::GPXTracksDir + "TrackDuration1.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.name(), 3 );	
}

// This test also covers the 'large quantity of points' point to a reasonable standard
BOOST_AUTO_TEST_CASE( totaltime_large_quantity)
{
   Route route = Route(LogFiles::GPXTracksDir + "TrackMultiplePoints.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.name(), 21000 );	
}


// Tests for earliest time out of order
BOOST_AUTO_TEST_CASE( totaltime_backwards)
{
   Route route = Route(LogFiles::GPXTracksDir + "N0702007TrackTimeEarliestOffset.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.name(), 40 );	
}

// Tests for latest time out of order
BOOST_AUTO_TEST_CASE( totaltime_backwards)
{
   Route route = Route(LogFiles::GPXTracksDir + "N0702007TrackTimeLatestOffset.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.name(), 40 );	
}




// Tests for time going backwards
BOOST_AUTO_TEST_CASE( totaltime_backwards)
{
   Route route = Route(LogFiles::GPXTracksDir + "N0702007TrackTimeBackwards.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.name(), 60 );	
}



// Tests for earliest time out of order, before last time
BOOST_AUTO_TEST_CASE( totaltime_backwards)
{
   Route route = Route(LogFiles::GPXTracksDir + "N0702007TrackTimeFirstBeforeLast.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.name(), 60 );	
}


// Tests for earliest time out of order, placed after last time
BOOST_AUTO_TEST_CASE( totaltime_backwards)
{
   Route route = Route(LogFiles::GPXTracksDir + "N0702007TrackTimeLastBeforeFirst.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.name(), 60 );	
}


// Tests for largest integer
BOOST_AUTO_TEST_CASE( totaltime_backwards)
{
   Route route = Route(LogFiles::GPXTracksDir + "N0702007TrackTimeLargestPossible.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.name(), 18446744073709551615 );	
}




BOOST_AUTO_TEST_SUITE_END()
