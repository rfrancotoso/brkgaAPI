/*
 * TSPDecoder.h
 *
 *  Created on: Mar 16, 2013
 *      Author: Rodrigo
 */

#ifndef TSPDECODER_H
#define TSPDECODER_H

#include "TSPSolver.h"
#include "TSPInstance.h"

class TSPDecoder {
public:
	TSPDecoder(const TSPInstance& instance);
	virtual ~TSPDecoder();

	// Decodes a chromosome into a solution to the TSP:
	double decode(const std::vector< double >& chromosome) const;

private:
	const TSPInstance& instance;
};

#endif
