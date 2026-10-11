/*util.cpp*/

/** 
 * @file util.cpp
 * @brief Helpful utility functions
 *
 * @author Prof Joe Hummel, Northwestern University
 */

#include <iostream>
#include <string>

#include "util.h"

using namespace std;


/** 
 * @brief returns the given string in lowercase
 *
 * @param s string
 * @return equivalent string in lowercase
 */
string toLower(string s)
{
  for (char& c : s) {
    c = tolower(c);
  }

  return s;
}
