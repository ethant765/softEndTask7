#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

#include "route.h"
#include "track.h"
#include "logs.h"

#include <stdexcept>
#include <iostream>
#include <fstream>

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_buildReport_tests )

BOOST_AUTO_TEST_CASE( test1 )
{
    std::string fileName = "NorthYorkMoors";
    const std::string filePath = LogFiles::GPXRoutesDir + fileName + ".gpx";
    const bool isFilename = true;
    Route route = Route(filePath, isFilename);
    std::string output;
    output = route.buildReport();

    std::string testFile = "route-buildReport-test.txt";

    std::ofstream out (testFile);
    out << output;
    out.close();

    std::ifstream in("route-buildReport-output.txt");

    std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

    std::ifstream testIn(testFile);

    std::string testContents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

    BOOST_CHECK( testContents == contents );
}

BOOST_AUTO_TEST_SUITE_END()
