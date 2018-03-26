#include <iostream>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

using std::cout;
using std::endl;

void testRoute(std::string fileName)
{
    const std::string filePath = LogFiles::GPXRoutesDir + fileName + ".gpx";

    const bool isFileName = true;

    Route route = Route(filePath,isFileName);

    cout << "Route name: " << route.name() << endl;
    cout << "Net Height Gain: " << route.netHeightGain() << endl;
    cout << "Total route length: " << route.totalLength() << endl;
    cout << endl;
}

int main()
{
    testRoute("NorthYorkMoors");
    testRoute("ABCD");
}
