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

void generateGPXTrack(std::string trackString,std::string trackName = "", int interval = 1, seconds timeUnitDuration = 10, seconds absoluteStartTime = 0, GridWorld gridWorld = GridWorld())
{
    const std::string filePath = LogFiles::GPXTracksDir + trackName + ".gpx";

    std::ofstream out (filePath);

    GridWorldTrack gridWorldRoute = GridWorldTrack(trackString,timeUnitDuration,absoluteStartTime, gridWorld);
    out << gridWorldRoute.toGPX(interval,true,trackName);
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

    generateGPXTrack("A1B2C", "TrackDuration1",1,1);
    generateGPXTrack("A3B1C", "TrackDuration10",1,10);
    generateGPXTrack("A4B2C", "TrackDurationEven",1,2);
    generateGPXTrack("M3A2G", "TrackDurationOdd",1,7);

}
