#include <sstream>

    #include <fstream>

    #include <iostream>

    #include <cassert>

    #include <cmath>

    #include <stdexcept>



    #include "geometry.h"

    #include "xmlparser.h"

    #include "track.h"



    using namespace GPS;



    // Note: The implementation should exploit the relationship:

    //   totalTime() == restingTime() + travellingTime()



    seconds Track::totalTime() const

    {

        const bool implemented = false;

        assert(implemented);

    }



    seconds Track::restingTime() const

    {

        const bool implemented = false;

        assert(implemented);

    }



    seconds Track::travellingTime() const

    {

        const bool implemented = false;

        assert(implemented);

    }



    speed Track::maxSpeed() const

    {

        const bool implemented = false;

        assert(implemented);

    }



    speed Track::averageSpeed(bool includeRests) const

    {

        const bool implemented = false;

        assert(implemented);

    }


    //N0687265
    speed Track::maxRateOfAscent() const
    {
        const bool implemented = true;
        assert(implemented);

        seconds time;
        metres elevation;
        speed rate, topRate = 0;
        for(unsigned long int i = 1; i < positions.size(); ++i){
            time = arrived[i] - departed[i-1];
            elevation = positions[i].elevation() - positions[i-1].elevation();
            rate = elevation / time;
            if(rate > topRate){
                topRate = rate;
            }
        }

        return topRate;
    }




    speed Track::maxRateOfDescent() const

    {

        const bool implemented = false;

        assert(implemented);

    }



    Track::Track(std::string sourceFile, bool isFileName, metres granularity)
    {
        using std::string;
        using std::ostringstream;

        using XML::Parser::getElementContent;
        using XML::Parser::getElement;
        using XML::Parser::elementExists;
        using XML::Parser::getAndEraseElement;
        using XML::Parser::getElementAttribute;

        ostringstream reportStream;

        this->granularity = granularity;

        string source = "";

        if (isFileName) {

            std::ifstream fs(sourceFile);

            if (! fs.good()) throw std::invalid_argument("Error opening source file '" + sourceFile + "'.");

            reportStream << "Source file '" << sourceFile << "' opened okay." << std::endl;


            ostringstream fileStream;

            while (fs.good()) {

                string lineHolder = "";

                getline(fs, lineHolder);

                fileStream << lineHolder << std::endl;

            }

            source = fileStream.str();

        }

        string GPXtemp = getElement(source, "gpx");

        string GPXsource = getElementContent(GPXtemp);

        string TRKtemp = getElement(GPXsource, "trk");

        string TRKsource = getElementContent(TRKtemp);

        if (elementExists(TRKsource, "name")) {

            string nameTemp = getAndEraseElement(TRKsource, "name");

            routeName = getElementContent(nameTemp);

            reportStream << "Track name is: " << routeName << std::endl;

        }

        string mergedTrkSegs = "";

        while (elementExists(TRKsource, "trkseg")) {

            string trksegTemp = getAndEraseElement(TRKsource, "trkseg");

            string trkseg = getElementContent(trksegTemp);

            getAndEraseElement(trkseg, "name");

            mergedTrkSegs += trkseg;

        }

        string mergedTrkSource = "";

        if (! mergedTrkSegs.empty()) mergedTrkSource = mergedTrkSegs;

        unsigned int numOfPositions = 0;

        string trkptTemp = getAndEraseElement(mergedTrkSource, "trkpt");


        string lat = getElementAttribute(trkptTemp, "lat");

        string lon = getElementAttribute(trkptTemp, "lon");

        string trkptElementTemp = getElementContent(trkptTemp);

        if (elementExists(trkptElementTemp, "ele")) {

            string tempEle = getElement(trkptElementTemp, "ele");

            string ele = getElementContent(tempEle);

            Position startPos = Position(lat,lon,ele);

            positions.push_back(startPos);

            reportStream << "Start position added: " << startPos.toString() << std::endl;

            ++numOfPositions;

        } else {

            Position startPos = Position(lat,lon);

            positions.push_back(startPos);

            reportStream << "Start position added: " << startPos.toString() << std::endl;

            ++numOfPositions;

        }

        string trkptElementName = "";

        if (elementExists(trkptElementTemp,"name")) {

            string tempName = getElement(trkptElementTemp,"name");

            trkptElementName = getElementContent(tempName);

        }

        positionNames.push_back(trkptElementName);

        arrived.push_back(0);

        departed.push_back(0);

        string tempTime = getElement(trkptElementTemp,"time");

        string trkptTime = getElementContent(tempTime);

        seconds startTime = stringToTime(trkptTime);

        seconds currentTime = stringToTime(trkptTime);

        Position prevPos = positions.back(), nextPos = positions.back();

        while (elementExists(mergedTrkSource, "trkpt")) {

            string temp = getAndEraseElement(mergedTrkSource, "trkpt");

            string tempLat = getElementAttribute(temp, "lat");

            string tempLon = getElementAttribute(temp, "lon");

            string tempContent = getElementContent(temp);

            if (elementExists(tempContent, "ele")) {

                string tempContentEle = getElement(tempContent, "ele");

                string tempEle = getElementContent(tempContentEle);

                nextPos = Position(tempLat,tempLon,tempEle);

            } else nextPos = Position(tempLat,tempLon);

            string tempContentTime = getElement(tempContent,"time");

            string strContentTime = getElementContent(tempContentTime);

            seconds contentTime = stringToTime(strContentTime);

            if (areSameLocation(nextPos, prevPos)) {

                // If we're still at the same location, then we haven't departed yet.

                departed.back() = contentTime - startTime;

                reportStream << "Position ignored: " << nextPos.toString() << std::endl;

            } else {

                string name = "";

                if (elementExists(tempContent,"name")) {

                    string tempContentName = getElement(tempContent,"name");

                    name = getElementContent(tempContentName);

                } else name = ""; // Fixed bug by adding this.

                positions.push_back(nextPos);

                positionNames.push_back(name);

                seconds timeElapsed = currentTime - startTime;

                arrived.push_back(timeElapsed);

                departed.push_back(timeElapsed);

                reportStream << "Position added: " << nextPos.toString() << std::endl;

                reportStream << " at time: " << std::to_string(timeElapsed) << std::endl;

                ++numOfPositions;

                prevPos = nextPos;

            }

        }

        reportStream << numOfPositions << " positions added." << std::endl;

        routeLength = 0;

        for (unsigned int i = 1; i < numOfPositions; ++i ) {

            metres deltaH = distanceBetween(positions[i-1], positions[i]);

            metres deltaV = positions[i-1].elevation() - positions[i].elevation();

            routeLength += sqrt(pow(deltaH,2) + pow(deltaV,2));

        }

        report = reportStream.str();

    }



    void Track::setGranularity(metres granularity)

    {

        bool implemented = false;

        assert(implemented);

    }



    seconds Track::stringToTime(const std::string & timeStr)

    {

        return stoull(timeStr);

    }

