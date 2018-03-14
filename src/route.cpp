#include <sstream>
#include <fstream>
#include <iostream>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <stdexcept>

#include "position.h"
#include "xmlparser.h"
#include "geometry.h"
#include "earth.h"
#include "route.h"

using namespace GPS;

std::string Route::name() const
{
   return routeName.empty() ? "Unnamed Route" : routeName;
}

unsigned int Route::numPositions() const
{
    const bool implemented = false;
    assert(implemented);
}

metres Route::totalLength() const
{
   metres totalLength;
   Position * lastPosition = nullptr;

   for(auto pos : positions)
   {
        if(lastPosition)
        {
            totalLength += distanceBetween(*lastPosition, pos);
        }

        lastPosition = &pos;
   }
    return routeLength;
}

metres Route::netLength() const
{
    std::vector<Position>::const_iterator first, last;
    first = positions.begin();
    last =  positions.end() - 1;
    return distanceBetween(*first, *last);
}

metres Route::totalHeightGain() const
{
    metres totalHeight;

    for(auto pos : positions){
        totalHeight += pos.elevation();
    }
     return totalHeight;
}

metres Route::netHeightGain() const
{
    std::vector<Position>::const_iterator first, last;
    first = positions.begin();
    last =  positions.end() - 1;

    return last->elevation() - first->elevation();
}

degrees Route::minLatitude() const
{
    degrees minLat = positions[0].latitude();
    for(auto pos : positions){
        if(pos.latitude() < minLat)
            minLat = pos.latitude();
    }
    return minLat;
}

degrees Route::maxLatitude() const
{
    degrees maxLat = positions[0].latitude();
    for(auto pos : positions){
        if(pos.latitude() > maxLat)
            maxLat = pos.latitude();
    }
    return maxLat;
}

degrees Route::minLongitude() const
{
    degrees minLong = positions[0].longitude();
    for(auto pos : positions){
        if(pos.longitude() < minLong)
            minLong = pos.longitude();
    }
    return minLong;
}

degrees Route::maxLongitude() const
{
    degrees maxLong = positions[0].longitude();
    for(auto pos : positions){
        if(pos.longitude() > maxLong)
            maxLong = pos.longitude();
    }
    return maxLong;
}

metres Route::minElevation() const
{
    degrees minElev = positions[0].elevation();
    for(auto pos : positions){
        if(pos.elevation() < minElev)
            minElev = pos.elevation();
    }
    return minElev;
}

metres Route::maxElevation() const
{
    degrees maxElev = positions[0].elevation();
    for(auto pos : positions){
        if(pos.elevation() > maxElev)
            maxElev = pos.elevation();
    }
    return maxElev;
}

degrees Route::maxGradient() const
{
    const bool implemented = false;
    assert(implemented);
}

degrees Route::minGradient() const
{
    const bool implemented = false;
    assert(implemented);
}

degrees Route::steepestGradient() const
{
    const bool implemented = false;
    assert(implemented);
}

Position Route::operator[](unsigned int idx) const
{
    const bool implemented = false;
    assert(implemented);
}

Position Route::findPosition(const std::string & soughtName) const
{
    const bool implemented = false;
    assert(implemented);
}

std::string Route::findNameOf(const Position & soughtPos) const
{
    const bool implemented = false;
    assert(implemented);
}

unsigned int Route::timesVisited(const std::string & soughtName) const
{
    const bool implemented = false;
    assert(implemented);
}

unsigned int Route::timesVisited(const Position & soughtPos) const
{
    const bool implemented = false;
    assert(implemented);
}

std::string Route::buildReport() const
{
    return report;
}

Route::Route(std::string source, bool isFileName, metres granularity)
{
    using namespace std;
    using namespace XML::Parser;
    string lat,lon,ele,name,temp,temp2;
    metres deltaH,deltaV;
    ostringstream oss,oss2;
    unsigned int num;
    this->granularity = granularity;
    if (isFileName){
        ifstream fs = ifstream(source);
        if (! fs.good()) throw invalid_argument("Error opening source file '" + source + "'.");
        oss << "Source file '" << source << "' opened okay." << endl;
        while (fs.good()) {
            getline(fs, temp);
            oss2 << temp << endl;
        }
        source = oss2.str();
    }
    if (! elementExists(source,"gpx")) throw domain_error("No 'gpx' element.");
    temp = getElement(source, "gpx");
    source = getElementContent(temp);
    if (! elementExists(source,"rte")) throw domain_error("No 'rte' element.");
    temp = getElement(source, "rte");
    source = getElementContent(temp);
    if (elementExists(source, "name")) {
        temp = getAndEraseElement(source, "name");
        routeName = getElementContent(temp);
        oss << "Route name is: " << routeName << endl;
    }
    num = 0;
    if (! elementExists(source,"rtept")) throw domain_error("No 'rtept' element.");
    temp = getAndEraseElement(source, "rtept");
    if (! attributeExists(temp,"lat")) throw domain_error("No 'lat' attribute.");
    if (! attributeExists(temp,"lon")) throw domain_error("No 'lon' attribute.");
    lat = getElementAttribute(temp, "lat");
    lon = getElementAttribute(temp, "lon");
    temp = getElementContent(temp);
    if (elementExists(temp, "ele")) {
        temp2 = getElement(temp, "ele");
        ele = getElementContent(temp2);
        Position startPos = Position(lat,lon,ele);
        positions.push_back(startPos);
        oss << "Position added: " << startPos.toString() << endl;
        ++num;
    } else {
        Position startPos = Position(lat,lon);
        positions.push_back(startPos);
        oss << "Position added: " << startPos.toString() << endl;
        ++num;
    }
    if (elementExists(temp,"name")) {
        temp2 = getElement(temp,"name");
        name = getElementContent(temp2);
    }
    positionNames.push_back(name);
    Position prevPos = positions.back(), nextPos = positions.back();
    while (elementExists(source, "rtept")) {
        temp = getAndEraseElement(source, "rtept");
        if (! attributeExists(temp,"lat")) throw domain_error("No 'lat' attribute.");
        if (! attributeExists(temp,"lon")) throw domain_error("No 'lon' attribute.");
        lat = getElementAttribute(temp, "lat");
        lon = getElementAttribute(temp, "lon");
        temp = getElementContent(temp);
        if (elementExists(temp, "ele")) {
            temp2 = getElement(temp, "ele");
            ele = getElementContent(temp2);
            nextPos = Position(lat,lon,ele);
        } else nextPos = Position(lat,lon);
        if (areSameLocation(nextPos, prevPos)) oss << "Position ignored: " << nextPos.toString() << endl;
        else {
            if (elementExists(temp,"name")) {
                temp2 = getElement(temp,"name");
                name = getElementContent(temp2);
            } else name = ""; // Fixed bug by adding this.
            positions.push_back(nextPos);
            positionNames.push_back(name);
            oss << "Position added: " << nextPos.toString() << endl;
            ++num;
            prevPos = nextPos;
        }
    }
    oss << num << " positions added." << endl;
    routeLength = 0;
    for (unsigned int i = 1; i < num; ++i ) {
        deltaH = distanceBetween(positions[i-1], positions[i]);
        deltaV = positions[i-1].elevation() - positions[i].elevation();
        routeLength += sqrt(pow(deltaH,2) + pow(deltaV,2));
    }
    report = oss.str();
}

void Route::setGranularity(metres granularity)
{
    bool implemented = false;
    assert(implemented);
}

bool Route::areSameLocation(const Position & p1, const Position & p2) const
{
    return (distanceBetween(p1,p2) < granularity);
}
