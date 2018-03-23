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

void generateGPXTrack(std::string trackString,std::string trackName = "", seconds Loginterval = 1,
                      seconds timeUnitDuration = 10, seconds absoluteStartTime = 0, GridWorld gridWorld = GridWorld())
{
    const std::string filePath = LogFiles::GPXTracksDir + trackName + ".gpx";

    std::ofstream out (filePath);

    GridWorldTrack gridWorldRoute = GridWorldTrack(trackString,timeUnitDuration,absoluteStartTime, gridWorld);
    out << gridWorldRoute.toGPX(Loginterval,true,trackName);
    out.close();
    cout << "file " + filePath + " written" << endl;
}

void testTrack(std::string fileName)
{
  const std::string filePath = LogFiles::GPXTracksDir + fileName + ".gpx";

  const bool isFileName = true;

  Track track = Track(filePath,isFileName);

  track.travellingTime();
}

int main()
{
    //GridWorld gridWorld = GridWorld(Earth::Pontianak,1000,0);
    generateGPXTrack("A1B2C", "TrackDuration1",1,1);
    generateGPXTrack("A3B1C", "TrackDuration10",1,10);
    generateGPXTrack("A4B2C", "TrackDurationEven",1,2);
    generateGPXTrack("M3A2G", "TrackDurationOdd",1,7);
    generateGPXTrack("R4U2A","TrackI&D1",1,1);
    generateGPXTrack("A2U4R","TrackInterval10",10);
    generateGPXTrack("M3A2G","TrackIntervalNegative",-1,1);
    //TODO All of these below
    generateGPXTrack("M3A2G","TrackIntervalEven",4,10);
    generateGPXTrack("M3A2G","TrackIntervalOdd",5,9);
    generateGPXTrack("A3B1C", "TrackAbsoluteTime1", 1,10,1);
    generateGPXTrack("A3B1C", "TrackAbsoluteTimeNegative", 1,10,-1);
    testTrack("TrackIntervalOdd");
}
