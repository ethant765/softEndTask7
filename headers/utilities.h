#ifndef UTILITIES_H_211217
#define UTILITIES_H_211217

#include <string>

#include "types.h"

using std::string;

namespace GPS
{
  // Convert from degrees to radians.
  radians degToRad(degrees);

  // Sine squared function: sin^2(x)
  double sinSqr(double);

  bool containsValidChars(const string & toCheck, const string & allowedChars);

  bool noAdjacentDuplicateChars(const string &);

  string removeDigitsFrom(string);

  string removeRepeatingCharsFrom(string);

  string timeAsString(seconds);

  seconds timeFromString (const string &);
}

#endif
