/*main.cpp*/

/** 
 * @file main.cpp
 * @brief main program to read positions and interact with user
 *
 * @author Prof Joe Hummel, Northwestern University
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>

#include "position.h"
#include "util.h"

using namespace std;


/** 
 * @brief inputs positions data from input file, stores into vector
 *
 * @param filename file to open
 * @param positions vector to fill with data (passed-by-ref)
 * @return true if successful, false if file could not be opened
 */
bool input_positions(string filename, vector<Position>& positions)
{
  ifstream file;
  file.open(filename);
  if (file.fail()) {
    cout << "file not found" << endl;
  }

  while (true) {
    double lat, lon;
    string ident, category;

    file >> lat;
    file >> lon;
    file >> ident;
    file >> category;

    if (file.fail()) {
      break;
    }

    positions.push_back(Position(lat, lon, ident, category));
  }
  return true;
}


/** 
 * @brief sorts positions by identifier
 *
 * @param positions vector to sort (passed-by-ref)
 * @return void
 */
void sort_positions(vector<Position>& positions)
{
  sort(positions.begin(), positions.end(),
      [](const Position& pos1, const Position& pos2) -> bool {
        return pos1.getIdentifier() < pos2.getIdentifier();
      });
}


/** 
 * @brief outputs each position in the vector, one per line
 *
 * @param position vector of position objects
 * @return void
 */
void output_positions(const vector<Position>& positions)
{
  for (const Position& pos : positions) {
    pos.print();
  }
}


/** 
 * @brief searches positions for a given identifier (case-insensitive)
 *
 * @param positions vector to search
 * @param identifier the identifier to search for
 * @return iterator to position or positions.end() if not found
 */
vector<Position>::const_iterator search(const vector<Position>& positions, string identifier)
{
  vector<Position>::const_iterator iter;

  //
  // TODO:
  //
  iter = find_if(positions.begin(), positions.end(), [=](const Position& pos) -> bool {
    return toLower(pos.getIdentifier()) == toLower(identifier);
  });
  return iter;
}


/** 
 * @brief searches for a given identifier and outputs if found
 *
 * @param positions vector to search
 * @param identifier the identifier to search for
 * @return void
 */
void find_position(const vector<Position>& positions, string identifier)
{
  vector<Position>::const_iterator res = search(positions, identifier);
  if (res == positions.end()) {
    cout << "not found" << endl;
    return;
  }

  res->print();
}


/** 
 * @brief removes the given position from vector (not underlying file)
 *
 * @param positions vector to search and remove from (passed-by-ref)
 * @param identifier the identifier to search for
 * @return void
 */
void remove_position(vector<Position>& positions, string identifier)
{
  vector<Position>::const_iterator res = search(positions, identifier);
  if (res == positions.end()) {
    cout << "not found" << endl;
    return;
  }

  positions.erase(res);
  cout << "removed" << endl;
}


/** 
 * @brief outputs distances to all the food positions from given identifier
 *
 * @param positions vector to search 
 * @param identifier the identifier to search for
 * @return void
 */
void closest_food(const vector<Position>& positions, string identifier)
{
  vector<pair<string, double>> food_distances;
  vector<Position>::const_iterator res = search(positions, identifier);
  if (res == positions.end()) {
    cout << "not found" << endl;
    return;
  }

  for (const Position& pos : positions) {
    if (pos.getCategory() == "food") {
      pair<string, double> p = make_pair(
        pos.getIdentifier(),
        res->distance(pos)
      );
      food_distances.push_back(p);
    }
  }

  sort(food_distances.begin(), food_distances.end(), [](const pair<string, double>& x, const pair<string, double>& y) {
    return x.second < y.second;
  });

  for (const auto& dist : food_distances) {
    cout << dist.first << ": " << dist.second << endl;
  }
}


int main()
{
  vector<Position> positions;
  
  bool success = input_positions("data.txt", positions);
  if (!success) {
    cout << "input file not found" << endl; 
    return 0;
  }
  
  sort_positions(positions);

  //
  // command loop:
  //
  string cmd;

  cout << endl;
  cout << "Enter command (p, c id, f id, r id, #): ";
  cin >> cmd;

  while (cmd != "#")
  {
    if (cmd == "p") {
      output_positions(positions);
    }
    else if (cmd == "c") {
      string identifier;
      cin >> identifier;

      closest_food(positions, identifier);
    }
    else if (cmd == "f") {
      string identifier;
      cin >> identifier;

      find_position(positions, identifier);
    }
    else if (cmd == "r") {
      string identifier;
      cin >> identifier;

      remove_position(positions, identifier);
    }
    else {
      cout << "unknown command" << endl;
    }

    cout << endl;
    cout << "Enter command (p, c id, f id, r id, #): ";
    cin >> cmd;
  }

  //
  // done:
  //
  return 0;
}
