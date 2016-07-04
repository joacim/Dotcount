/* Dotcount - This program counts black separate regions (dots) in an image.
 * Copyright (C) 2009-2016  Joacim Thomassen
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
 * Initial date: 28-1-2009
 * Changed date: 30-7-2011
 *
 * dotcount.cpp
 */

#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include "commonTypes.hpp"

using std::string;
using std::vector;
using std::cerr;
using std::cout;
using std::endl;
using std::set;
using std::pair;
using std::ofstream;



bool versionRequest(int argc, char **argv) {
    return argc == 2 && string(argv[1]) == "--version";
}


int main(int argc, char *argv[]) {

    if (versionRequest(argc, argv)) {
	cout << PROGRAM << " " << VERSION << " " << VERDATE << endl;
	return EXIT_SUCCESS;
    }

    ProgramInput programInput = ProgramInput(argc, argv);
    if (programInput.validCheckOk() == false) {
	return EXIT_FAILURE;
    }

    DotSeeker dotSeeker = DotSeeker(programInput);
    dotSeeker.run();
    if (dotSeeker.validResultCheckOk() == false) {
	cerr << "Error: Invalid result." << endl;
	return EXIT_FAILURE;
    }
    const Result &result = dotSeeker.getResult();
	
    if (DEBUG) {
	result.printAllDots();
    }

    result.writeDotMarkedImage(programInput);
    
    result.writeDotDiametersToFile(programInput);

    result.writeReportLogToFile(programInput);

    return EXIT_SUCCESS;
}
