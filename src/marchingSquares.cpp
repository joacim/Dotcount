/* Dotcount - This program counts black separate regions (dots) in an image.
 * Copyright (C) 2009-2011  Joacim Thomassen
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
 * The marchingSquares module is based on Tom Gibara's Java implementation of 
 * the Marching Squares algorithm. See the CREDITS file for more information.
 *
 * This module extracts paths defining elements in a given binary matrix.
 * The algorithm used to trace connected cells in the matrix is called the 
 * marching squares algorithm.
 *
 * Initial date: 31-10-2009
 * Changed date: 30-7-2011
 *
 * TODO: Refactor: Too cryptic, make easier to apprehend. Need more levels of
 *       abstraction. 10/3-2011
 *
 * marchingSquares.cpp
 */

#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include "marchingSquares.hpp"
#include "direction.hpp"

using std::vector;
using std::cerr;
using std::cout;
using std::endl;


typedef size_t state; // 0..15 possible states in Marching Squares



MarchingSquares::MarchingSquares(const BinMatrix &data)
    : data_(data), height(data.rowSize()), width(data.colSize()), 
      visitedCells(height * width, false)
{ }

void MarchingSquares::identify_perimeter(const size_t initial_x, 
					 const size_t initial_y,
					 Result &result)
{
    assert(initial_x < width && initial_y < height);

    state initial_state = getState(initial_x, initial_y);
    if (initial_state == 0 || initial_state == 15) {
	// Supplied initial state do not lie on a perimeter!
	return;
    }

    vector<const Direction*> directions;
    int x = initial_x;
    int y = initial_y;
    const Direction *previous = NULL;
    size_t nextCellNo = y * width + x;

    do {
	const Direction *direction = NULL;
	state currState = 0;
	switch (currState = getState(x, y)) {
	case  1: direction = Heading::north; break;
	case  2: direction = Heading::east; break;
	case  3: direction = Heading::east; break;
	case  4: direction = Heading::west; break;
	case  5: direction = Heading::north; break;
	case  6: if (previous == Heading::north)
		     direction = Heading::west;
		 else
		     direction = Heading::east;
		 break;
	case  7: direction = Heading::east; break;
	case  8: direction = Heading::south; break;
	case  9: if (previous == Heading::east)
		     direction = Heading::north;
		 else
		     direction = Heading::south;
		 break;
	case 10: direction = Heading::south; break;
	case 11: direction = Heading::south; break;
	case 12: direction = Heading::west; break;
	case 13: direction = Heading::north; break;
	case 14: direction = Heading::west; break;
	default: cerr << "Illegal state!\n"; exit(1);
	}
	directions.push_back(direction);

	if (DEBUG) {
	    cout << "(" << y << "," << x << ") going " 
		 << direction->textPrint() << "(" << currState << ")" << " to ";
	}

	x += direction->screenX();
	y += direction->screenY();
	previous = direction;
	nextCellNo = y * width + x;
	if (nextCellNo < width * height 
		&& visitedCells.at(nextCellNo) == true) {
	    return;
	}
    } while (x != static_cast<int>(initial_x) 
	    || y != static_cast<int>(initial_y));

    if (DEBUG) {
	cout << endl;
    }

    // marking only visited initial (path origin)  perimeter cell
    size_t initCellNo = initial_y * width + initial_x;
    if (initCellNo < width * height) {
	visitedCells.at(initCellNo) = true;
    }

    result.addPerimeter(Path(initial_x, initial_y, directions));
}

void MarchingSquares::identify_perimeter_paths(Result &result) { 
    for (size_t i = 0; i < height * width; ++i) {
	if (data_.cell(i) != 0 && !visitedCells.at(i)) {
	    identify_perimeter(i % width, i / width, result);
	}
    }
}

state MarchingSquares::getState(const int x, const int y) const {
    state sum = 0;
    if (isSet(x, y)) sum |= 1;
    if (isSet(x + 1, y)) sum |= 2;
    if (isSet(x, y + 1)) sum |= 4;
    if (isSet(x + 1, y + 1)) sum |= 8;
    return sum;
}

bool MarchingSquares::isSet(const int x, const int y) const {
    return x <= 0 || x > static_cast<int>(width) || y <= 0 
	   || y > static_cast<int>(height) 
	   ? false : data_.cell(y - 1, x - 1) != 0;
}



void perimeterSeeker(const ProgramInput &programInput, Result &result) {
    MarchingSquares ms(programInput.getBinMatrix());
    ms.identify_perimeter_paths(result);
}
