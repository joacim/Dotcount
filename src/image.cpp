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
 * Initial date: 25-2-2010
 * Changed date: 30-7-2011
 *
 * image.cpp
 */

extern "C" {
#include <pam.h>
}
#include <unistd.h>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include "image.hpp"
#include "binaryMatrix.hpp"

using std::string;
using std::vector;
using std::cerr;
using std::cout;



PnmImage::PnmImage(const string &fileName) 
    : fileName_(fileName), input(NULL), tuplerow(NULL), row(0) 
{ }

PnmImage::~PnmImage() {
    if (input) {
        fclose(input);
    }
}

string PnmImage::baseName() const {
    size_t suffixPos = fileName_.rfind(".");
    if (suffixPos == std::string::npos) {
	std::cerr << "Irregular filname for " << fileName_ << "\n";
    }
    return string(fileName_.begin(), fileName_.begin() + suffixPos);
}

const string &PnmImage::fullName() const {
    return fileName_;
}

bool PnmImage::read() {
    if (!(input = fopen(fileName_.c_str(), "r"))) {
	std::cerr << "Failed to open " << fileName_ << "\n";
	return false;
    }
    pnm_readpaminit(input, &image, sizeof(image));
    return true;
}

bool PnmImage::write(const PnmImage &src) {
    if (!(input = fopen(fileName_.c_str(), "w"))) {
	std::cerr << "Failed to open " << fileName_ << "\n";
	return false;
    }
    image = src.getPam();
    image.file = input;
    pnm_writepaminit(&image);
    return true;
}

bool PnmImage::remove() {
    if (!(input = fopen(fileName_.c_str(), "w"))) {
	std::cerr << "Failed to open " << fileName_ << "\n";
	return false;
    }
    fclose(input);
    unlink(fileName_.c_str());
    return true;
}

size_t PnmImage::height() const {
    return image.height;
}

size_t PnmImage::width() const {
    return image.width;
}

size_t PnmImage::depth() const {
    return image.depth;
}

const char *PnmImage::imageType() const {
    return image.tuple_type;
}

const struct pam &PnmImage::getPam() const {
    return image;
}

void PnmImage::writeTupleRow(const tuple *newTupleRow) {
    pnm_writepamrow(&image, newTupleRow); 
}


bool pnmToBinMatrix(const PnmImage &src, BinMatrix &dst) {
    struct pam imgHeader = src.getPam();
    tuple *tuplerow = pnm_allocpamrow(&imgHeader);
    if (!tuplerow) {
	cerr << "Input error: Something wrong with src image!\n";
	return false;
    }
    for (size_t row = 0; row < src.height(); row++) {
	pnm_readpamrow(&imgHeader, tuplerow);
	for (size_t column = 0; column < src.width(); ++column) {
	    for (size_t plane = 0; plane < src.depth(); ++plane) {
		if (src.depth() != 1) { // sample is 0 or 255
		    cerr << "Input error: Image " << src.fullName() 
			 << " must have two colors (binary).\n";
		    exit(1);
		}
		bool value = tuplerow[column][plane];
		value = !value; // inverted as Pnm(0=BLACK) != BinMatrix(0=WHITE)
		dst.insert(row, column, value);
	    }
	}
    }
    pnm_freepamrow(tuplerow);
    tuplerow = NULL;
    return true;
}


/* duplicate image and mark tuples touched by identified_paths */
bool duplicateAndMark(const PnmImage &src, 
                      std::set<std::pair<int, int> > &perimeterPixels, 
		      PnmImage &dst) 
{
    struct pam imgHeader = src.getPam();
    tuple *tuplerow = pnm_allocpamrow(&imgHeader);
    if (!tuplerow) {
	cerr << "Input error: Something wrong with src image.\n";
	return false;
    }
    for (size_t row = 0; row < src.height(); row++) {
	pnm_readpamrow(&imgHeader, tuplerow);
	for (size_t col = 0; col < src.width(); ++col) {
	    if (perimeterPixels.find(std::make_pair(col, row)) 
                != perimeterPixels.end()) 
	    {
		tuplerow[col][0] = 255;
		tuplerow[col][1] = 0;
		tuplerow[col][2] = 0;
	    }
	}
	dst.writeTupleRow(tuplerow);
    }
    if (!tuplerow) {
	cerr << "Input error: Something wrong with image.\n";
	return false;
    }
    pnm_freepamrow(tuplerow);
    return true;
}

bool isRGBCheckOk(const PnmImage &src) {
    struct pam imgHeader = src.getPam();
    tuple *tuplerow = pnm_allocpamrow(&imgHeader);
    if (!tuplerow) {
	cerr << "Input error: Something wrong with src image!\n";
	return false;
    }
    const string imageType = string(src.imageType());
    pnm_freepamrow(tuplerow);
    tuplerow = NULL;
    return (imageType == PAM_PPM_TUPLETYPE);
}

bool isGreyscaleCheckOk(const PnmImage &src) {
    struct pam imgHeader = src.getPam();
    tuple *tuplerow = pnm_allocpamrow(&imgHeader);
    if (!tuplerow) {
	cerr << "Input error: Something wrong with src image!\n";
	return false;
    }
    const string imageType = string(src.imageType());
    pnm_freepamrow(tuplerow);
    tuplerow = NULL;
    return (imageType == PAM_PGM_TUPLETYPE);
}
