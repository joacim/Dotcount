/* Dotcount - This program counts black separate regions (dots) in an image.
 * Copyright (C) 2010-2013  Joacim Thomassen
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
 * The seeker module is based on Tom Gibara's Java implementation of the 
 * Marching Squares algorithm. See the CREDITS file for more information.
 *
 * Initial date: 15-1-2010
 * Changed date: 30-7-2011
 *
 * marchingSquares.hpp
 */

#ifndef MARCHING_SQUARES_HPP
#define MARCHING_SQUARES_HPP

#ifndef DEBUG
#define DEBUG 0
#endif

#include <vector>
#include <cstddef>
#include "binaryMatrix.hpp"
#include "commonTypes.hpp"



class MarchingSquares {
public:
    MarchingSquares(const BinMatrix &data);
    void identify_perimeter(const size_t initial_x, const size_t initial_y, 
			    Result &result);
    void identify_perimeter_paths(Result &result);
private:
    typedef size_t state; // 0..15 possible states in Marching Squares
    state getState(const int x, const int y) const;
    bool isSet(const int x, const int y) const;

    const BinMatrix &data_;
    size_t height;
    size_t width;
    std::vector<bool> visitedCells;
};



void perimeterSeeker(const ProgramInput &programInput, Result &result);

#endif
