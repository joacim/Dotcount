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
 * The direction module is based on Tom Gibara's Java implementation of the 
 * Marching Squares algorithm. See the CREDITS file for more information.
 *
 * Initial date: 1-3-2011
 * Changed date: 30-7-2011
 *
 * direction.hpp
 */

#ifndef DIRECTION_HPP 
#define DIRECTION_HPP 

#include <vector>
#include <string>
#include <cstddef>



class Direction {
public:
    Direction(const int x, const int y);
    const int screenX() const;
    const int screenY() const;
    virtual const std::string textPrint() const;
private:
    int plane_x;
    int plane_y;
    int screen_x;
    int screen_y;
    double length;
};



class North : public Direction {
public:
    North();
    const int screenX() const;
    const int screenY() const;
    virtual const std::string textPrint() const;
private:
    int plane_x;
    int plane_y;
    int screen_x;
    int screen_y;
    double length;
};



class South : public Direction {
public:
    South();
    const int screenX() const;
    const int screenY() const;
    virtual const std::string textPrint() const;
private:
    int plane_x;
    int plane_y;
    int screen_x;
    int screen_y;
    double length;
};



class East : public Direction {
public:
    East();
    const int screenX() const;
    const int screenY() const;
    virtual const std::string textPrint() const;
private:
    int plane_x;
    int plane_y;
    int screen_x;
    int screen_y;
    double length;
};



class West : public Direction {
public:
    West();
    const int screenX() const;
    const int screenY() const;
    const std::string textPrint() const;
private:
    int plane_x;
    int plane_y;
    int screen_x;
    int screen_y;
    double length;
};



class Nowhere : public Direction {
public:
    Nowhere();
    const int screenX() const;
    const int screenY() const;
    const std::string textPrint() const;
private:
    int plane_x;
    int plane_y;
    int screen_x;
    int screen_y;
    double length;
};



namespace Heading {
    extern const Direction *north;
    extern const Direction *south;
    extern const Direction *east;
    extern const Direction *west;
}

#endif
