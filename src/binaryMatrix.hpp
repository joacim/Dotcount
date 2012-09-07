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
 * Initial date: 1-3-2011
 * Changed date: 30-7-2011
 *
 * binaryMatrix.hpp
 */

#ifndef BINARY_MATRIX_HPP
#define BINARY_MATRIX_HPP

#include <vector>
#include <cstddef>



class BinMatrix {
public:
    BinMatrix(const size_t rowSize = 0, const size_t colSize = 0);
    void insert(const size_t row, const size_t column, const bool value);
    size_t rowSize() const;
    size_t colSize() const;
    bool cell(const size_t row, const size_t column) const;
    bool cell(const size_t index) const;
private:
    std::vector<bool> data; // 0, false = WHITE; 1, true = BLACK
    size_t rowSize_;
    size_t colSize_;
};

#endif
