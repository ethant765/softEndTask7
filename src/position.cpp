#include <cassert>
#include <cmath>
#include <sstream>

#include "position.h"
#include "utilities.h"

namespace GPS
{
  Position::Position(degrees lat, degrees lon, metres ele)
  {
      this->lat = lat;
      this->lon = lon;
      this->ele = ele;
  }

  Position::Position(const string & latStr,
                     const string & lonStr,
                     const string & eleStr)
  {
      lat = std::stod(latStr);
      lon = std::stod(lonStr);
      ele = std::stod(eleStr);
  }

  Position::Position(const string & ddmLatStr, char northing,
                     const string & ddmLonStr, char easting,
                     const string & eleStr)
  {
      assert(northing == 'N' || northing == 'S');
      assert(easting  == 'E' || easting  == 'W');

      degrees absoluteLat = ddmTodd(ddmLatStr);
      degrees absoluteLon = ddmTodd(ddmLonStr);

      // N/S and E/W are used with positive angles.
      assert(absoluteLat >= 0);
      assert(absoluteLon >= 0);

      lat = (northing == 'N') ? absoluteLat : -absoluteLat; // 'S' means negative angle
      lon = (easting  == 'E') ? absoluteLon : -absoluteLon; // 'W' means negative angle
      ele = std::stod(eleStr);
  }

  degrees Position::latitude() const
  {
      return lat;
  }

  degrees Position::longitude() const
  {
      return lon;
  }

  metres Position::elevation() const
  {
      return ele;
  }

  string Position::toString(bool includeElevation) const
  {
      std::ostringstream oss;

      oss << "lat=\""  << lat  << "\"";
      oss << " lon=\"" << lon << "\"";
      if (includeElevation) {
          oss << " ele=\"" << ele << "\"";
      }

      return oss.str();
  }

  /* Convert a DDM (degrees and decimal minutes) string representation of an angle to a
     DD (decimal degrees) value.
   */
  degrees ddmTodd(const string & ddmStr)
  {
      double ddm  = std::stod(ddmStr);
      double degs = std::floor(ddm / 100);
      double mins = ddm - 100 * degs;
      return degs + mins / 60.0; // converts minutes (1/60th) to decimal fractions of a degree
  }

  /* Computes an approximation of the distance between two Positions.
   *
   * See: http://en.wikipedia.org/wiki/Law_of_haversines
   */
  metres distanceBetween(const Position & p1, const Position & p2)
  {
      const metres earth_mean_radius = 6371008.8;

      const radians lat1 = degToRad(p1.latitude());
      const radians lat2 = degToRad(p2.latitude());
      const radians lon1 = degToRad(p1.longitude());
      const radians lon2 = degToRad(p2.longitude());

      double h = sinSqr((lat2-lat1)/2) + cos(lat1)*cos(lat2)*sinSqr((lon2-lon1)/2);
      return 2 * earth_mean_radius * asin(sqrt(h));
  }
}
