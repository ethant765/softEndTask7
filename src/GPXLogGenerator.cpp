#include "../headers/gridworld_route.h"
#include "gridworld.h"
#include "logs.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace GPS;

int main() {
 Position position = Earth::CityCampus;
 //makes the gridworld and sets position (Campus) to 'M'
 //parameters the set position (lat,lon,ele), the difference in lat/lon, the difference in elevaion
 GridWorld gridworld = GridWorld(position, 5000, 0);
 //Generates the GPX.log based on the route given
 GridWorldRoute route = GridWorldRoute("MHGBA", gridworld);
 //Generate Log files for testing
 std::ofstream GPXLog;
 GPXLog.open(LogFiles::GPXRoutesDir + "n0680788_minElevation_null.gpx");
 GPXLog << route.toGPX();
 GPXLog.close();
 return 0;
}
