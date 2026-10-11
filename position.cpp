/*position.cpp*/

/** 
 * @file position.cpp
 * @brief Position class
 *
 * Positions are given in (latitude, longitude). Latitudes are 
 * positive above the equator and negative below; longitudes are
 * positive heading east of Greenwich and negative heading west.
 * Example: Chicago is (41.88, -87.63).
 *
 * @author Prof Joe Hummel, Northwestern University
 */

#include <iostream>
#include <string>
#include <cmath>

#include "position.h"

using namespace std;


//
// private function to convert degrees to radians:
//
static double toRadians(double degrees)
{
  return (degrees * 3.141592653589 / 180.0);
}


//
// constructor:
//
Position::Position(double lat, double lon, string identifier, string category)
  : Latitude(lat), Longitude(lon), Identifier(identifier), Category(category)
{ }


//
// distance (in miles) from this position to other position:
//
// Reference: chatGPT using haversine formula
//
double Position::distance(const Position& other) const
{
  const double R = 6371; // Earth's radius in kilometers

  double lat1 = this->Latitude;
  double lat2 = other.Latitude;
  double lon1 = this->Longitude;
  double lon2 = other.Longitude;

  double dLat = toRadians(lat2 - lat1);
  double dLon = toRadians(lon2 - lon1);

  double a = sin(dLat / 2) * sin(dLat / 2) +
    cos(toRadians(lat1)) * cos(toRadians(lat2)) *
    sin(dLon / 2) * sin(dLon / 2);

  double c = 2 * atan2(sqrt(a), sqrt(1 - a));

  double dist_in_km = R * c;

  double dist_in_miles = dist_in_km * 0.6213711922;

  return dist_in_miles;
}


//
// print as one line to console:
//
void Position::print() const
{
  cout << this->Identifier << ": "
       << this->Category << " @ ("
       << this->Latitude << ", "
       << this->Longitude << ")"
       << endl;
}


//
// getters
//
double Position::getLat() const { return this->Latitude; }
double Position::getLon() const { return this->Longitude; }
string Position::getIdentifier() const { return this->Identifier; }
string Position::getCategory() const { return this->Category; }
