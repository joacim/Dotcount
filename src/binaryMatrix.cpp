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
 * Initial date: 1-3-2011
 * Changed date: 30-7-2011
 *
 * binaryMatrix.cpp
 */

#include <cstddef>
#include "binaryMatrix.hpp"



BinMatrix::BinMatrix(const size_t rowSize, const size_t colSize) 
    : data(rowSize * colSize, false), rowSize_(rowSize), colSize_(colSize)
{ }

void BinMatrix::insert(const size_t row, const size_t column, const bool value)
{
    data.at(row * colSize_ + column) = value;
}

size_t BinMatrix::rowSize() const { return rowSize_; }

size_t BinMatrix::colSize() const { return colSize_; }

bool BinMatrix::cell(const size_t row, const size_t column) const {
    return data.at(row * colSize_ + column);
}

bool BinMatrix::cell(const size_t index) const {
    return data.at(index);
}
