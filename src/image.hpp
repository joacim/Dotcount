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
 * Initial date: 14-2-2010
 * Changed date: 30-7-2011
 *
 * image.hpp
 */

#ifndef IMAGE_HPP
#define IMAGE_HPP

extern "C" {
#include <pam.h>
}
#include <string>
#include <cstddef>
#include <set>
#include "binaryMatrix.hpp"



class PnmImage {
public:
	PnmImage(const std::string &fileName = "");
	~PnmImage();

	std::string baseName() const;
	const std::string &fullName() const;
	bool read();
	bool write(const PnmImage &src);
	bool remove();
	size_t height() const;
	size_t width() const;
	size_t depth() const;
	const char *imageType() const;
	const struct pam &getPam() const;
	void writeTupleRow(const tuple *newTupleRow);
private:
	std::string fileName_;
	FILE *input;
	struct pam image;
	tuple *tuplerow;
	int row;
};



bool pnmToBinMatrix(const PnmImage &src, BinMatrix &dst);

bool duplicateAndMark(const PnmImage &src, 
		      std::set<std::pair<int, int> > &perimeterPixels, 
		      PnmImage &dst);

bool isRGBCheckOk(const PnmImage &src);

bool isGreyscaleCheckOk(const PnmImage &src);

#endif
