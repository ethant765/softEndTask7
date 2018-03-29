#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_name )

const bool isFileName = true;

/*
	Function: Total Time
	
	Tests/Considerations & Explanations:
	
	CORRECT: 
	
		Regular input:
		Testing correct input ensures the function works as expected.
		
		
		Correct input, data not ordered correctly by time (1 value incorrectly placed):
		Though I'm not sure if this should throw an error, the data is still technically valid, and testing & fixing for this will result in more robust code.
		The multiple cases for this test I'll cover are:
			Time going backwards
			Largest time out of place (Not first nor last)
			Smallest time out of place (Not first nor last)
			Smallest time immediately before largest time
			Smallest time immediately after largest time
			
		
		
		Correct input, maximum values for inputs:
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
		Incorrect types would throw an error at 'Track::StringToTime' and would not reach this function.
		
		Incorrect & Correct input, multiple track segments
		The transformation from XML to Route or Track combines all track segments into a single set of data.
		
		Incorrect values for variables other than 'Time'
		Given the functions' purpose doesn't utilise any variables other than 'Time' in the given track, 
		
*/



// Test for correct values
BOOST_AUTO_TEST_CASE( totaltime_stationary_points )
{
   Route route = Route(LogFiles::GPXTracksDir + "TrackDuration1.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.name(), 1 );	
}





BOOST_AUTO_TEST_SUITE_END()
