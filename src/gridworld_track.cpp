#include <algorithm>
#include <stdexcept>
#include <cctype>
#include <cassert>
#include <sstream>

#include "xmlgenerator.h"
#include "gridworld_route.h"
#include "gridworld_track.h"

using namespace GPS;

GridWorldTrack::GridWorldTrack(std::string trackStr, seconds timeUnitDur, seconds absStartTime, GridWorld gridworld)
  : trackString{trackStr},
    gridworld{gridworld},
    timeUnitDuration{timeUnitDur},
    startTime{absStartTime}
{
    if (! isValidTrackString(trackStr)) throw std::invalid_argument("Invalid point sequence, cannot construct Track.");
    constructWaypoints();
}

void GridWorldTrack::constructWaypoints()
{
    std::istringstream tss(trackString);

    GridWorld::Point point;
    unsigned int timeUnits;
    while (tss >> point)
    {
        waypoints.push_back(point);
        tss >> timeUnits;
        timeUnitsToNextWaypoint.push_back(timeUnits);
    }
    timeUnitsToNextWaypoint.pop_back(); // Discard any time units after the final waypoint.

    assert(waypoints.size() == (timeUnitsToNextWaypoint.size() + 1));
}

string GridWorldTrack::toGPX(seconds logInterval, bool embedName, const std::string& trackName) const
{
    XML::Generator gpx;

    gpx.basicXMLHeader();
    gpx.openBasicGPXElement();

    gpx.openElement("trk","");
    if (embedName)
    {
        std::string name = trackName.empty() ? trackString : trackName;
        gpx.element("name", "", name);
    }

    const bool includeElevation = false; // For Position interface

    std::vector<unsigned int>::const_iterator timeUnitsIt = timeUnitsToNextWaypoint.begin();
    std::vector<GridWorld::Point>::const_iterator pointsIt = waypoints.begin();

    seconds segmentStartTime = startTime;

    GridWorld::Point currentPoint = *pointsIt;
    ++pointsIt;
    for (; pointsIt != waypoints.end(); ++pointsIt, ++timeUnitsIt)
    {
        GridWorld::Point nextPoint = *pointsIt;
        gpx.openElement("trkseg","");

        const string segmentName = string(1,currentPoint) + "-" + string(1,nextPoint);
        gpx.element("name","",segmentName);

        seconds timeThisSegment = (*timeUnitsIt) * timeUnitDuration;
        seconds segmentEndTime = segmentStartTime + timeThisSegment;
        double stepsThisSegment = timeThisSegment / logInterval;

        const Position& currentPos = gridworld[currentPoint];
        const Position& nextPos = gridworld[nextPoint];
        degrees deltaLat = (nextPos.latitude() - currentPos.latitude()) / stepsThisSegment;
        degrees deltaLon = (nextPos.longitude() - currentPos.longitude()) / stepsThisSegment;
        metres deltaEle = (nextPos.elevation() - currentPos.elevation()) / stepsThisSegment;

        degrees lat = currentPos.latitude();
        degrees lon = currentPos.longitude();
        metres ele = currentPos.elevation();
        for (seconds currentTime = segmentStartTime; currentTime <= segmentEndTime; currentTime += logInterval)
        {
            Position pos = Position(lat, lon, ele);
            gpx.openElement("trkpt", pos.toString(includeElevation));
            gpx.element("ele", "",std::to_string(pos.elevation()));
            gpx.element("time","",std::to_string(currentTime));
            gpx.closeElement(); // "trkpt"

            lat += deltaLat;
            lon += deltaLon;
            ele += deltaEle;
        }

        segmentStartTime = segmentEndTime;
        gpx.closeElement(); // "trkseg"

        currentPoint = nextPoint;
        segmentStartTime = segmentEndTime;
    }

    return gpx.closeAllElementsAndExtractString();
}

std::string GridWorldTrack::toString() const
{
    return trackString;
}

bool GridWorldTrack::isValidTrackString(const string & trackStr)
{
    bool validChars = std::all_of(trackStr.begin(), trackStr.end(),
                                  [] (char c) {return std::isupper(c) || std::isdigit(c);});
    bool noLeadingOrTrailingTime = trackStr.length() == 0 || (isupper(trackStr.front()) && isupper(trackStr.back()));
    return validChars && noLeadingOrTrailingTime && GridWorldRoute::isValidRouteString(routeStringFromTrackString(trackStr));
}

std::string GridWorldTrack::routeStringFromTrackString(const string & trackStr)
{
    std::string routeStr = trackStr;
    routeStr.erase(std::remove_if(routeStr.begin(),routeStr.end(),[] (char c) {return std::isdigit(c);}),
                   routeStr.end());
    return routeStr;
}
