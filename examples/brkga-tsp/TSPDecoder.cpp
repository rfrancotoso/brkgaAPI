/*
 * TSPDecoder.cpp
 *
 *  Created on: Mar 16, 2013
 *      Author: Rodrigo
 */

#include "TSPDecoder.h"

TSPDecoder::TSPDecoder(const TSPInstance& _instance) : instance(_instance) {
}

TSPDecoder::~TSPDecoder() {
}

double TSPDecoder::decode(const std::vector< double >& chromosome) const {
	// 1) Solve the problem (i.e., create a tour out of this chromosome):
	// Avoids race conditions by making sure we have a single TSPSolver for each thread calling
	// ::decode (as long as TSPSolver does not make use of 'static' or other gimmicks):
	TSPSolver solver(instance, chromosome);

	// 2) Extract the fitness (tour distance):
	const unsigned fitness = solver.getTourDistance();

	// 3) Return:
	return double(fitness);
}

