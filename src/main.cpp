#include <iostream>
#include <fstream>

#include "logs.h"
#include "route.h"
#include "track.h"
#include "gridworld_route.h"
#include "gridworld_track.h"

using namespace GPS;

using std::cout;
using std::endl;

void testRoute(std::string fileName)
{
    const std::string filePath = LogFiles::GPXRoutesDir + fileName + ".gpx";
    const bool isFileName = true;
<<<<<<< HEAD

    Route route = Route(filePath, isFileName);
=======
    Route route = Route(filePath,isFileName);
>>>>>>> netHeightGain

    cout << "Route name: " << route.name() << endl;
    cout << "Net Height Gain: " << route.netHeightGain() << endl;
    cout << "Min elevation: " << route.minElevation() << endl;
    cout << "Max elevation: " << route.maxElevation() << endl;

//    Track track = Track(filePathTrack, isFileName);
//    const std::string filePathTrack = LogFiles::GPXTracksDir + fileName + ".gpx";
//    cout << "Route name: " << track.name() << endl;
//    cout << "Net Height Gain: " << track.netHeightGain() << endl;
    cout << endl;
}

int main()
{
    testRoute("NorthYorkMoors");
    testRoute("ABCD");
    //testRoute("negativeElevation");
    testRoute("ZigZag");
    //testRoute("positiveElevation");
}

