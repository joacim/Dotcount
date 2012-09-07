/* Dotcount - This program counts black separate regions (dots) in an image.
 * Copyright (C) 2011  Joacim Thomassen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * The author can be contacted by e-mail at this address:
 * joacim@net.homelinux.org
 *
 * The path module is based on Tom Gibara's Java implementation of the 
 * Marching Squares algorithm. See the CREDITS file for more information.
 *
 * Initial date: 1-3-2011
 * Changed date: 30-7-2011
 *
 * path.cpp
 */

#include <sstream>
#include <vector>
#include <string>
#include "path.hpp"
#include "direction.hpp"

using std::string;
using std::vector;
using std::stringstream;



Path::Path(const int start_x, const int start_y, 
	   const vector<const Direction*> &directions)
    : origin_x(start_x), origin_y(start_y), 
      directionList(directions.begin(), directions.end())
{ }

const string Path::textPrint() const {
    stringstream tmp;
    tmp << origin_y << "," << origin_x << " - ";
    for (size_t i = 0; i < directionList.size(); ++i) {
	tmp << directionList[i]->textPrint() << " - ";
    }
    return tmp.str();
}

const vector<const Direction*> &Path::getDirections() const {
    return directionList;
}

int Path::getOriginX() const { return origin_x; }

int Path::getOriginY() const { return origin_y; }

