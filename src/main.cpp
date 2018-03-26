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

void generateGPXRoute(string route, string routeName)
{
  GridWorldRoute test = GridWorldRoute(route);
  const std::string filePath = LogFiles::GPXRoutesDir + routeName + ".gpx";
  std::ofstream out(filePath);
  out << test.toGPX(true, routeName);
  out.close();
  cout << "File: " << filePath << " has been written" << endl;
}

void testRoute(std::string fileName)
{
    const std::string filePath = LogFiles::GPXRoutesDir + fileName + ".gpx";

    const bool isFileName = true;

    Route route = Route(filePath, isFileName);

    cout << "Route name: " << route.name() << endl;
    // cout << "Number of positions in route: " << route.numPositions() << endl;
    cout << "Total route length: " << route.totalLength() << endl;
    // cout << "Net route length: " << route.netLength() << endl;
    cout << endl;
}

int main()
{
    testRoute("NorthYorkMoors");
    testRoute("ABCD");
    generateGPXRoute("AMG", "test1");
}
