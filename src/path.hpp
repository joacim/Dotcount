/* Dotcount - This program counts black separate regions (dots) in an image.
 * Copyright (C) 2011-2016  Joacim Thomassen
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
 * The path module is based on Tom Gibara's Java implementation of the 
 * Marching Squares algorithm. See the CREDITS file for more information.
 *
 * Initial date: 1-3-2011
 * Changed date: 30-7-2011
 *
 * path.hpp
 */

#ifndef PATH_HPP
#define PATH_HPP

#include <vector>
#include <string>
#include "direction.hpp"



class Path {
public:
    Path(const int start_x, const int start_y, 
	    const std::vector<const Direction*> &directions);
    const std::string textPrint() const;
    const std::vector<const Direction*> &getDirections() const;
    int getOriginX() const;
    int getOriginY() const;
private:
    int origin_x;
    int origin_y;
    int terminal_x;
    int terminal_y;
    std::vector<const Direction*> directionList;
    double length;
};

#endif
