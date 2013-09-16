/* Dotcount - This program counts black separate regions (dots) in an image.
 * Copyright (C) 2011-2013  Joacim Thomassen
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
 *
 * The direction module is based on Tom Gibara's Java implementation of the 
 * Marching Squares algorithm. See the CREDITS file for more information.
 *
 * Initial date: 1-3-2011
 * Changed date: 30-7-2011
 *
 * direction.cpp
 */

#include <string>
#include <cmath>
#include "direction.hpp"

using std::string;



namespace Heading {
    const Direction *north = new North();
    const Direction *south = new South();
    const Direction *east = new East();
    const Direction *west = new West();
}



Direction::Direction(const int x, const int y)
    : plane_x(x), plane_y(y), screen_x(x), screen_y(-y), 
      length(x != 0 && y != 0 ? sqrt(2.0) / 2.0 : 1.0)
{ }

const int Direction::screenX() const {
    return screen_x;
}

const int Direction::screenY() const {
    return screen_y;
}

const string Direction::textPrint() const {
    return "Unknown";
}



North::North() : Direction(0, 1) { }

const string North::textPrint() const {
    return "North";
}



South::South() : Direction(0, -1) { }

const string South::textPrint() const {
    return "South";
}



East::East() : Direction(1, 0) { }

const string East::textPrint() const {
    return "East";
}



West::West() : Direction(-1, 0) { }

const string West::textPrint() const {
    return "West";
}



Nowhere::Nowhere() : Direction(0, 0) { }

const string Nowhere::textPrint() const {
    return "Nowhere";
}
