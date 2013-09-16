/* Dotcount - This program counts black separate regions (dots) in an image.
 * Copyright (C) 2009-2013  Joacim Thomassen
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
 * Simple unit test for the marchingSquares module.
 *
 * Initial date: 31-10-2009
 * Changed date: 30-7-2011
 *
 * marchingSquaresTest.cpp
 */

#include <vector>
#include <iostream>
#include "path.hpp"
#include "image.hpp"
#include "direction.hpp"
#include "commonTypes.hpp"
#include "binaryMatrix.hpp"
#include "marchingSquares.hpp"

using std::vector;
using std::cerr;
using std::cout;
using std::endl;



int main(int argc, char *argv[]) {
    const size_t rowSize = 5;
    const size_t colSize = 5;
    bool a_matrix[rowSize][colSize] = { { 0, 1, 0, 0, 0 },
					{ 1, 0, 1, 0, 1 },
					{ 0, 1, 0, 1, 1 },
					{ 1, 0, 0, 1, 0 },
					{ 0, 1, 1, 0, 1 } };

    bool b_matrix[rowSize][colSize] = { { 0, 1, 0, 0, 0 },
					{ 1, 0, 0, 0, 1 },
					{ 0, 1, 0, 1, 1 },
					{ 0, 1, 0, 1, 0 },
					{ 1, 0, 1, 0, 1 } };

    bool c_matrix[rowSize][colSize] = { { 0, 1, 0, 0, 0 },
					{ 1, 0, 1, 1, 1 },
					{ 0, 1, 1, 1, 1 },
					{ 0, 1, 1, 1, 1 },
					{ 1, 0, 1, 0, 1 } };

    BinMatrix matrix = BinMatrix(rowSize, colSize);
    for (size_t row = 0; row < rowSize; ++row) {
	for (size_t col = 0; col < colSize; ++col) {
	    matrix.insert(row, col, a_matrix[row][col]);
	}
    }

    cout << "Unit test for MarchingSquares module.\nChecking matrix: \n";
    for (size_t row = 0; row < rowSize; ++row) {
	for (size_t col = 0; col < colSize; ++col) {
	    cout << matrix.cell(row, col) << ", ";
	}
	cout << endl;
    }

    MarchingSquares ms(matrix);
    Result result;
    ms.identify_perimeter_paths(result);

    cout << "Finished identifying paths for dot perimeters. Found " 
	 << result.dotCount() << " dots in matrix.\n";
    result.printAllDots();
    return 0;
}
