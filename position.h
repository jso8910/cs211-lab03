/*position.h*/

/** 
 * @file position.h
 * @brief Position class
 *
 * Positions are given in (latitude, longitude). Latitudes are 
 * positive above the equator and negative below; longitudes are
 * positive heading east of Greenwich and negative heading west.
 * Example: Chicago is (41.88, -87.63).
 *
 * @author Prof Joe Hummel, Northwestern University
 */

#pragma once

#include <string>

using namespace std;


class Position
{
private:
  double Latitude;
  double Longitude;
  string Identifier;
  string Category;

public:
  // constructor
  Position(double lat, double lon, string identifier, string category);

  // distance (in miles) from this position to other position:
  double distance(const Position& other) const;

  // print as one line to console:
  void print() const;

  // getters
  double getLat() const;
  double getLon() const;
  string getIdentifier() const;
  string getCategory() const;
};
