#include <sstream>
#include <fstream>
#include <iostream>
#include <cassert>
#include <cmath>
#include <stdexcept>

#include "xmlparser.h"
#include "geometry.h"
#include "earth.h"
#include "route.h"
#include "position.h"
using namespace GPS;

//route constructor
Route::Route(std::string sourceFile, bool isFileName, metres granularity)
{
    using std::invalid_argument;
    using std::domain_error;
    using std::endl;
    using std::string;
    using std::ostringstream;
    using std::ifstream;

    using XML::Parser::elementExists;
    using XML::Parser::getElement;
    using XML::Parser::getAndEraseElement;
    using XML::Parser::attributeExists;
    using XML::Parser::getElementContent;
    using XML::Parser::getElementAttribute;

    string ele = "";
    string name = "";
    string source = "";
    metres deltaH = 0.0, deltaV = 0.0;
    ostringstream reportStream;
    unsigned int numOfPositions = 0;
    this->granularity = granularity;

    if (isFileName){
        source = readFile(sourceFile, reportStream);
    }

    if (! elementExists(source,"gpx")) throw domain_error("No 'gpx' element.");
    string tempElementGpx = getElement(source, "gpx");
    source = getElementContent(tempElementGpx);
    if (! elementExists(source,"rte")) throw domain_error("No 'rte' element.");
    string tempElementRte = getElement(source, "rte");
    source = getElementContent(tempElementRte);
    if (elementExists(source, "name")) {
        tempElementRte = getAndEraseElement(source, "name");
        routeName = getElementContent(tempElementRte);
        reportStream << "Route name is: " << routeName << endl;
    }


    if (! elementExists(source,"rtept")) throw domain_error("No 'rtept' element.");
    string tempElementRtept = getAndEraseElement(source, "rtept");
    if (! attributeExists(tempElementRtept,"lat")) throw domain_error("No 'lat' attribute.");
    if (! attributeExists(tempElementRtept,"lon")) throw domain_error("No 'lon' attribute.");

    string lat = getElementAttribute(tempElementRtept, "lat");
    string lon = getElementAttribute(tempElementRtept, "lon");
    string tempElementRteptContent = getElementContent(tempElementRtept);
    if (elementExists(tempElementRteptContent, "ele")) {
        ele = getElementContent(getElement(tempElementRteptContent, "ele"));
        Position startPos = Position(lat,lon,ele);
        positions.push_back(startPos);
        reportStream << "Position added: " << startPos.toString() << endl;
        ++numOfPositions;
    } else {
        Position startPos = Position(lat,lon);
        positions.push_back(startPos);
        reportStream << "Position added: " << startPos.toString() << endl;
        ++numOfPositions;
    }
    if (elementExists(tempElementRteptContent,"name")) {
        name = getElementContent(getElement(tempElementRteptContent,"name"));
    }
    positionNames.push_back(name);
    Position prevPos = positions.back(), nextPos = positions.back();
    while (elementExists(source, "rtept")) {
        string rtept = getAndEraseElement(source, "rtept");
        if (! attributeExists(rtept,"lat")) throw domain_error("No 'lat' attribute.");
        if (! attributeExists(rtept,"lon")) throw domain_error("No 'lon' attribute.");
        string lat = getElementAttribute(rtept, "lat");
        string lon = getElementAttribute(rtept, "lon");
        string rteptContent = getElementContent(rtept);
        if (elementExists(rteptContent, "ele")) {
            ele = getElementContent(getElement(rteptContent, "ele"));
            nextPos = Position(lat,lon,ele);
        } else nextPos = Position(lat,lon);
        if (areSameLocation(nextPos, prevPos)) reportStream << "Position ignored: " << nextPos.toString() << endl;
        else {
            if (elementExists(rteptContent,"name")) {
                string reteptContentName = getElement(rteptContent,"name");
                name = getElementContent(reteptContentName);
            } else name = ""; // Fixed bug by adding this.
            positions.push_back(nextPos);
            positionNames.push_back(name);
            reportStream << "Position added: " << nextPos.toString() << endl;
            ++numOfPositions;
            prevPos = nextPos;
        }
    }
    reportStream << numOfPositions << " positions added." << endl;
    routeLength = 0;
    for (unsigned int i = 1; i < numOfPositions; ++i ) {
        deltaH = distanceBetween(positions[i-1], positions[i]);
        deltaV = positions[i-1].elevation() - positions[i].elevation();
        routeLength += sqrt(pow(deltaH,2) + pow(deltaV,2));
    }
    report = reportStream.str();
}

std::string Route::readFile(std::string file, std::ostringstream& streamReference){
    using std::ifstream;
    using std::string;
    using std::ostringstream;
    using std::endl;

    ostringstream fileContent;

    ifstream fs(file);
    if (! fs.good()) throw std::invalid_argument("Error opening source file '" + file + "'.");
    streamReference << "Source file '" << file << "' opened okay." << endl;
    while (fs.good()) {
        string temp = "";
        getline(fs, temp);
        fileContent << temp << endl;
    }
    return fileContent.str();
}

std::string Route::name() const
{
   return routeName.empty() ? "Unnamed Route" : routeName;
}

unsigned int Route::numPositions() const
{
    const bool implemented = true;
    assert(implemented);
    
    return positions.size();
}

metres Route::totalLength() const
{
    return routeLength;
}

metres Route::netLength() const
{
    const bool implemented = true;
    assert(implemented);



    metres distance = distanceBetween(positions[0],positions.back());
    return distance;
}

metres Route::totalHeightGain() const
{
    metres heightGain = 0;
    if (positions.size() > 1)
    {
        for (unsigned int i = 1; i<positions.size(); ++i)
        {
            if (positions[i].elevation()-positions[i-1].elevation()>0)
            {
                heightGain += positions[i].elevation()-positions[i-1].elevation();
            }
        }
    }
    return heightGain;
}

metres Route::netHeightGain() const
{
    std::vector<Position>::const_iterator first, last;
    first = positions.begin();
    last =  positions.end() - 1;
    if (last->elevation() - first->elevation() > 0){
        return last->elevation() - first->elevation();
    }
    else{
        return 0;
    }
}

degrees Route::minLatitude() const
{
    const bool implemented = true;
    assert(implemented);
//    degrees minLat = positions[0].latitude();
//    for(unsigned int i = 1; i < positions.length(); i++)
//    {
//        if(positions[i].latitude() < minLat)
//        {
//            minLat = positions[i].latitude();
//        }
//    }
//    return minLat;
    degrees minLat = positions[0].latitude();
    for(unsigned int i = 1; i < positions.size(); i++)
    {
        if(positions[i].latitude() < minLat)
        {
            minLat = positions[i].latitude();
        }
    }
    if (minLat < -90 || minLat > 90)
        throw std::out_of_range ("out of range");
    return minLat;
}

degrees Route::maxLatitude() const
{
    const bool implemented = true;

    assert(implemented);

    int Maximum = 0;
    for (int i = 0; i < positions.size() ; i++)
    {

        if (positions[i].latitude() > positions[Maximum].latitude()) {
            Maximum = i;
        }

    }

    return positions[Maximum].latitude();
}

degrees Route::minLongitude() const
{
     const bool implemented = false;
    assert(implemented);

}

degrees Route::maxLongitude() const
{
    const bool implemented = true;

    assert(implemented);

    int MaximumIndex = 0;
    for (unsigned int i = 0; i < positions.size() ; i++)
    {

        if ((positions[i].longitude() > 180) || (positions[i].longitude() < -180)){
            throw std::out_of_range("Not in bounds of long");
        }

        if (positions[i].longitude() > positions[MaximumIndex].longitude()) {
            MaximumIndex = i;
        }

    }

    return positions[MaximumIndex].longitude();
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

metres Route::maxElevation() const // N0669298
{
    if (positions.size() == 0)
    {
        throw std::invalid_argument("No positions in provided route");
    }    
    degrees maxElev = positions[0].elevation();
    for(auto pos : positions){
        if(pos.elevation() > maxElev)
            maxElev = pos.elevation();
    }
    return maxElev;
}

degrees Route::maxGradient() const
{
    const bool implemented = true;
    assert(implemented);
    //
    if (positions.size()<2) return 0;


    degrees largestGradient;
    degrees testGradient;
 
    if (distanceBetween(positions[0],positions[1])>0) {
        largestGradient =radToDeg(atan2((positions[1].elevation() - positions[0].elevation()),distanceBetween(positions[1],positions[0])));
        testGradient = largestGradient;

    }

    else {
        if (positions[0].elevation() <positions[1].elevation()){
        largestGradient =90;
        testGradient = 90;}
        else if (positions[0].elevation() >positions[1].elevation())
        {
            largestGradient =-90;
            testGradient = -90;
        }
        else{
            largestGradient =0;
            testGradient = 0;
        }
}
    for(size_t x = 2; x < positions.size(); x++){

        if (distanceBetween(positions[x],positions[x-1])>0){
          testGradient =
                  radToDeg(atan2((positions[x].elevation() - positions[x-1].elevation()),
                  distanceBetween(positions[x],positions[x-1])));
        }
        else if (positions[0].elevation() <positions[1].elevation())
        {
            testGradient = 90;
        }
        else if (positions[0].elevation() >positions[1].elevation())
        {
            testGradient = -90;
        }
        else
        {
            testGradient = 0;
        }


        if(testGradient > largestGradient){
             largestGradient = testGradient;
        }
        
     }
    return largestGradient;
}

degrees Route::minGradient() const
{
    const bool implemented = true;
    assert(implemented);

    if (positions.size()<2)
    {
        throw std::invalid_argument("Gradient cannot be worked out when using only one point");
    }

    degrees minGradient;
    degrees temp, deltaH,deltaV;

    deltaH = distanceBetween(positions[0], positions[1]);
    deltaV = positions[0].elevation() - positions[1].elevation();

    minGradient=sqrt(pow(deltaH,2) + pow(deltaV,2));
    if(deltaV==0)
    {
        minGradient=0;
    }
    if (positions[0].elevation() > positions[1].elevation())
    {
        minGradient = -minGradient;
    }
    for (unsigned int i = 2; i < positions.size(); ++i )
    {
        deltaH = distanceBetween(positions[i-1], positions[i]);
        deltaV = positions[i-1].elevation() - positions[i].elevation();
        temp= sqrt(pow(deltaH,2) + pow(deltaV,2));
        if(deltaV==0)
        {
            temp=0;
        }
        if(positions[i-1].elevation() > positions[i].elevation())
        {
            temp = -temp;
        }

        if(temp<minGradient)
        {
            minGradient=temp;
        }
    }
    return minGradient;

}

degrees Route::steepestGradient() const
{
    const bool implemented = false;
    assert(implemented);
}

Position Route::operator[](unsigned int idx) const
{
    return positions.at(idx);
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



void Route::setGranularity(metres granularity)
{
    bool implemented = false;
    assert(implemented);
}

bool Route::areSameLocation(const Position & p1, const Position & p2) const
{
    return (distanceBetween(p1,p2) < granularity);
}
