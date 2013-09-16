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
 * Initial date: 1-2-2011
 * Changed date: 30-7-2011
 *
 * commonTypes.cpp
 */

#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <cassert>
#include <string>
#include "commonTypes.hpp"
#include "image.hpp"
#include "binaryMatrix.hpp"
#include "path.hpp"
#include "marchingSquares.hpp"

using std::string;
using std::set;
using std::pair;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;
using std::ofstream;



ProgramInput::ProgramInput(int argc, char **argv) : nm_range_(0), px_range_(0) {
    for (int i = 0; i < argc; ++i) {
        argv_.push_back(string(*(argv + i)));
    }
    if (validArgCount()) {
        nm_range_ = static_cast<double>(atoi(argv[3]));
        px_range_ = static_cast<double>(atoi(argv[4]));
    }
    if (validRanges()) {
	if (initImageHandler() == true) {
	    matrix = BinMatrix(preparedImage_.height(), preparedImage_.width());
	    if (isRGBCheckOk(originalImage_) == false) {
	    	cerr << "Input error: Image " << originalImage_.fullName()
		     << " is not a valid RGB image.\n";
		markedImage_.remove(); // cleanup from initImageHandler()
		exit(1);
	    }
	    if (isGreyscaleCheckOk(preparedImage_) == false) {
	    	cerr << "Input error: Image " << preparedImage_.fullName()
		     << " is not a valid greyscale image.\n";
		markedImage_.remove(); // cleanup from initImageHandler()
		exit(1);
	    }
	    pnmToBinMatrix(preparedImage_, matrix);
	}
    }
}

bool ProgramInput::validCheckOk() const {
    if (!validArgCount()) {
	cerr << "Usage: dotcount <prepared_image.pnm>"
	     << " <original_image.pnm> <nm_range> <px_range>\n";
    }
    else if (!validRanges()) {
	cerr << "Input error: Scale values must be positive integers "
	     << "greater than zero." << endl;
    }
    else {
	return true;
    }
    return false;
}

const double ProgramInput::nm_range() const { 
    return nm_range_;
}

const double ProgramInput::px_range() const { 
    return px_range_;
}

const double ProgramInput::scale() const { 
    return nm_range_ / px_range_;
}

const BinMatrix &ProgramInput::getBinMatrix() const {
    return matrix;
}

bool ProgramInput::initImageHandler() {
    pm_init(argv_[0].c_str(), 0);
    preparedImage_ = PnmImage(argv_[1]);
    originalImage_ = PnmImage(argv_[2]);
    markedImage_ = PnmImage(originalImage_.baseName() + "_marked.pnm");
    if (!preparedImage_.read()) {
	cerr << "Failed to read " << preparedImage_.fullName() << endl;
	return false;
    }
    if (!originalImage_.read()) {
	cerr << "Failed to read " << originalImage_.fullName() << endl;
	return false;
    }
    if (!markedImage_.write(originalImage_)) {
	cerr << "Failed to write " << markedImage_.fullName() << endl;
	return false;
    }
    return true;
}

bool ProgramInput::validArgCount() const {
    return (argv_.size() == validArgumentCount);
}

bool ProgramInput::validRanges() const {
    return (nm_range_ > 0 && px_range_ > 0);
}

const PnmImage &ProgramInput::getOriginalImage() const {
    return originalImage_;
}
    
PnmImage &ProgramInput::getMarkedImage() {
    return markedImage_;
}

const PnmImage &ProgramInput::getPreparedImage() const {
    return preparedImage_;
}



Result::Result() { }

Result::~Result() { }

void Result::addPerimeter(const Path &path) {
    identifiedDots_.push_back(path);
}

bool Result::validCheckOk() const {
    return !identifiedDots_.empty();
}

/* dot = perimeter = unique path */
size_t Result::dotCount() const {
    return identifiedDots_.size();
}

void Result::printAllDots() const {
    cout << "Identified " << dotCount() << " paths.\n";
    for (vector<Path>::const_iterator path = identifiedDots_.begin(); 
	 path != identifiedDots_.end(); ++path) {
	cout << "Path: " << path->textPrint() << endl;
    }
    
}

void Result::writeDotMarkedImage(ProgramInput &programInput) const {
    typedef pair<int, int> pixel;
    set<pixel> perimeterPixels;
    vector<Path>::const_iterator perimeterPath = identifiedDots_.begin();
    while (perimeterPath != identifiedDots_.end()) {
	// save origin x,y
	int ox = perimeterPath->getOriginX();
	int oy = perimeterPath->getOriginY();
	perimeterPixels.insert(std::make_pair(ox, oy));
	const vector<const Direction*> dir = perimeterPath->getDirections();
	vector<const Direction*>::const_iterator d = dir.begin();
	while (d != dir.end()) {
	    ox += (*d)->screenX();
	    oy += (*d)->screenY();
	    assert(0 <= ox && 0 <= oy);
	    perimeterPixels.insert(std::make_pair(ox, oy));
	    ++d;
	}
	++perimeterPath;
    }
    duplicateAndMark(programInput.getOriginalImage(), 
	             perimeterPixels, programInput.getMarkedImage());
}

/* Approximated diameter */
bool Result::writeDotDiametersToFile(const ProgramInput &programInput) const {
    string plotfile = programInput.getOriginalImage().baseName() + ".plot";
    ofstream outplot(plotfile.c_str());
    if (!outplot) {
	cerr << "Error writing to plotfile failed\n";
	return false;
    }
    vector<Path>::const_iterator it = identifiedDots_.begin();
    for (;it != identifiedDots_.end(); ++it)  { 
	const vector<const Direction*> dir = it->getDirections();
	outplot << (dir.size() * programInput.scale()) / M_PI << endl;
    }
    return true;
}

int Result::calcAverageCircumference() const {
    int sum_circumference = 0;
    vector<Path>::const_iterator it = identifiedDots_.begin();
    for (;it != identifiedDots_.end(); ++it)  { 
	const vector<const Direction*> dir = it->getDirections();
	sum_circumference += dir.size();
    }
    return sum_circumference / dotCount();
}

bool Result::writeReportLogToFile(ProgramInput &programInput) const {
    string logfile = programInput.getOriginalImage().baseName() + ".log";
    ofstream outlog(logfile.c_str());
    if (!outlog) {
	cerr << "Error writing to logfile failed\n";
	return false;
    }
    /* ProgramInput::density() => percent, etc., PI::areaInPixels() */
    double preparedImageHeight = programInput.getPreparedImage().height(); 
    double preparedImageWidth = programInput.getPreparedImage().width(); 
    double preparedImageArea = preparedImageHeight * preparedImageWidth;
    int averageCircumference = calcAverageCircumference();
    outlog << "Processed by: " << PROGRAM << " " << VERSION << " " << VERDATE 
	   << "\n"
	   << "Sample: " << programInput.getOriginalImage().baseName() << "\n"
	   << "nm range: " << programInput.nm_range() << "\n"
	   << "px range: " << programInput.px_range() << "\n"
    	   << "Density per px²: " 
	   << double(dotCount()) / double(preparedImageArea) << " dots/px²\n" 
	   << "Density per cm²: "
	   << (double(dotCount())\
	      / double(preparedImageArea * pow(programInput.scale(), 2.0)))\
	      * pow(10.0,14.0)
	   << " dots/cm²\nDots: " << dotCount() << "\n"
	   << "Total area in px²: " << preparedImageArea << " px²\n"
	   << "Image height: " 
	   << preparedImageHeight * programInput.scale() * pow(10.0, -3.0) 
	   << " um²\n"
	   << "Image width: " 
	   << preparedImageWidth * programInput.scale() * pow(10.0, -3.0) 
	   << " um²\n"
	   << "Total area in um²: " 
	   << preparedImageArea * pow(programInput.scale(), 2.0) \
	      * pow(10.0, -6.0) << " um²\n"
	   << "Average circumference in px: " << averageCircumference << " px"
	   << " (~ Avg.D: " << averageCircumference / M_PI << " px)\n"
	   << "Average circumference in nm: " 
	   << (averageCircumference * programInput.scale()) << " nm"
	   << " (~ Avg.D: " 
           << (averageCircumference * programInput.scale()) / M_PI 
	   << " nm)\n";
    return true;
}



DotSeeker::DotSeeker(ProgramInput &programInput) : programInput_(programInput) { }

DotSeeker::~DotSeeker() { }

void DotSeeker::run() {
    perimeterSeeker(programInput_, result_); 
}

bool DotSeeker::validResultCheckOk() const {
    return result_.validCheckOk();
}

const Result &DotSeeker::getResult() const {
    return result_;
}
