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
    //GridWorld gridWorld = GridWorld(Earth::Pontianak);
    generateGPXTrack("A1B2C", "TrackDuration1",1,1);
    generateGPXTrack("A3B1C", "TrackDuration10",1,10);
    generateGPXTrack("A4B2C", "TrackDurationEven",1,2);
    generateGPXTrack("M3A2G", "TrackDurationOdd",1,7);
    generateGPXTrack("R4U2A","TrackI&D1",1,1);
    generateGPXTrack("A2U4R","TrackInterval10",10);
    generateGPXTrack("M3A2G","TrackIntervalNegative",-1,1);
    generateGPXTrack("M3A2G","TrackIntervalEven&lessthanhalf",5,20);
    generateGPXTrack("M3A2G","TrackI&DMultiplesOdd",3,9);
    generateGPXTrack("M3A2G","TrackI&DNotMultiples",3,7);
    generateGPXTrack("A3B1C", "TrackAbsoluteTime1", 1,10,1);
    generateGPXTrack("A3B1C", "TrackAbsoluteTimeNegative", 1,10,-1);
    generateGPXTrack("A7X2E1U4M2V5G", "TrackMultiplePoints", 100,1000);
    generateGPXTrack("A3A2B1M", "TrackHasRests", 1,10);
    generateGPXTrack("A0A2M2M", "TrackHas0andRests", 1,10);
}
