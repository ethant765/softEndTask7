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

void generateGPXRoute(std::string points)
{
    const std::string filePath = LogFiles::GPXRoutesDir + points + ".gpx";

    std::ofstream out (filePath);

    GridWorldRoute gridWorldRoute = GridWorldRoute(points);
    out << gridWorldRoute.toGPX();
    out.close();
    cout << "file " + filePath + " written" << endl;
}

void generateGPXTrack(std::string track)
{
    const std::string filePath = LogFiles::GPXTracksDir + track + ".gpx";

    std::ofstream out (filePath);

    GridWorldTrack gridWorldRoute = GridWorldTrack(track);
    out << gridWorldRoute.toGPX(1);
    out.close();
    cout << "file " + filePath + " written" << endl;
}

void testRoute(std::string fileName)
{
    const std::string filePath = LogFiles::GPXRoutesDir + fileName + ".gpx";

    const bool isFileName = true;

    Route route = Route(filePath,isFileName);

    cout << "Route name: " << route.name() << endl;
    // cout << "Number of positions in route: " << route.numPositions() << endl;
    cout << "Total route length: " << route.totalLength() << endl;
    // cout << "Net route length: " << route.netLength() << endl;
    cout << endl;
}

void testTrack(std::string fileName)
{
  const std::string filePath = LogFiles::GPXTracksDir + fileName + ".gpx";

  const bool isFileName = true;

  Track track = Track(filePath,isFileName);

  cout << "timeTravelling() is " << track.travellingTime() << endl;
  cout << endl;
}

int main()
{
    //testRoute("NorthYorkMoors");
    //testRoute("ABCD");
    //testTrack("A1B3C");
    generateGPXTrack("A1B");
    testTrack("A1B");
}
