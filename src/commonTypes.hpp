/* Dotcount - This program counts black separate regions (dots) in an image.
 * Copyright (C) 2011-2014  Joacim Thomassen
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
 * Changed date: 16-2-2014
 *
 * commonTypes.hpp
 */

#ifndef COMMON_TYPES_HPP
#define COMMON_TYPES_HPP

#ifndef DEBUG
#define DEBUG 0
#endif

#include <vector>
#include <string>
#include "image.hpp"
#include "binaryMatrix.hpp"
#include "path.hpp"
#include "commonTypes.hpp"

const std::string PROGRAM = "Dotcount";
const std::string VERSION = "2.3";
const std::string VERDATE = "(2014-2-16)";



class ProgramInput {
public:
    ProgramInput(int argc, char **argv);
    bool validCheckOk() const;
    const double nm_range() const;
    const double px_range() const;
    const double scale() const;
    const BinMatrix &getBinMatrix() const;
    const PnmImage &getOriginalImage() const;
    PnmImage &getMarkedImage();
    const PnmImage &getPreparedImage() const;
private:
    static const size_t validArgumentCount = 5;
    bool initImageHandler();
    bool validArgCount() const;
    bool validRanges() const;
    double nm_range_;
    double px_range_;
    std::vector<std::string> argv_;
    PnmImage preparedImage_;
    PnmImage originalImage_;
    PnmImage markedImage_;
    BinMatrix matrix;
};



class Result {
public:
    Result();
    ~Result();
    void addPerimeter(const Path &path);
    bool validCheckOk() const;
    size_t dotCount() const;
    void printAllDots() const;
    void writeDotMarkedImage(ProgramInput &) const;
    bool writeDotDiametersToFile(const ProgramInput &) const;
    int calcAverageCircumference() const;
    bool writeReportLogToFile(ProgramInput &programInput) const;
private:
    std::vector<Path> identifiedDots_;
};



class DotSeeker {
public:
    DotSeeker(ProgramInput &programInput);
    ~DotSeeker();
    void run();
    bool validResultCheckOk() const;
    const Result &getResult() const;
private:
    ProgramInput &programInput_;
    Result result_;
};

#endif
