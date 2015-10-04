# Makefile for interpolation template
#
# Add your headerfile to the sineTest: line.

sineTest: sineTest.h sineTest.cpp LeastSquareSine17.h LeastSquareSine.h Makefile
	g++ -std=c++0x -Ofast -o sineTest sineTest.cpp

picalc: picalc.cpp
	g++ -std=c++0x -Ofast -o picalc picalc.cpp

all: sineTest

clear:
	rm -f sineTest
