# Makefile for dotcount
# Copyright 2011-2013 Joacim Thomassen
#
# `ulimit -c unlimited` # to allow corefiles of unlimited size in bash
#
ALL_DEBUG_OPT=-Wall -pedantic -ggdb -g3 -O0 -DDEBUG
DEBUG_OPT=-Wall -pedantic -ggdb -g3 -O0
PROD_OPT=-Wall

#OPT=${DEBUG_OPT}
OPT=${PROD_OPT}

OBJS=binaryMatrix.o image.o direction.o path.o commonTypes.o marchingSquares.o

## Dotcount ##
dotcount: ${OBJS} dotcount.cpp
	g++ ${OPT} -o dotcount dotcount.cpp ${OBJS} -lnetpbm
marchingSquares.o: marchingSquares.cpp marchingSquares.hpp
	g++ ${OPT} -c marchingSquares.cpp
commonTypes.o: commonTypes.cpp commonTypes.hpp
	g++ ${OPT} -c commonTypes.cpp
path.o: path.cpp path.hpp
	g++ ${OPT} -c path.cpp
direction.o: direction.cpp direction.hpp
	g++ ${OPT} -c direction.cpp
image.o: image.cpp image.hpp
	g++ ${OPT} -c image.cpp
binaryMatrix.o: binaryMatrix.cpp binaryMatrix.hpp
	g++ ${OPT} -c binaryMatrix.cpp

## Unit Tests ##
test: ${OBJS} marchingSquaresTest.cpp
	g++ ${DEBUG_OPT} -o marchingSquaresTest marchingSquaresTest.cpp ${OBJS} -lnetpbm

## Install ##
install: 
	cp dotcount /usr/local/bin/dotcount

## Clean Up ##
clean:
	rm -f dotcount marchingSquaresTest *.o 
