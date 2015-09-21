/*
 * TSPSolver.cpp
 *
 *  Created on: Mar 16, 2013
 *      Author: Rodrigo
 */

#include "TSPSolver.h"

TSPSolver::TSPSolver(const TSPInstance& instance, const std::vector< double >& chromosome) :
		distance(0), tour(instance.getNumNodes()) {
	// Assumes that instance.getNumNodes() == chromosome.size() of course

	// 1) Obtain a permutation out of the chromosome -- this will be the tour:
	for(unsigned i = 0; i < chromosome.size(); ++i) { tour[i] = ValueKeyPair(chromosome[i], i); }

	// Here we sort 'rank', which will produce a permutation of [n] stored in ValueKeyPair::second:
	std::sort(tour.begin(), tour.end());

	// 2) Compute the distance of the tour given by the permutation:
	for(unsigned i = 1; i < tour.size(); ++i) {
		// Compute distance(i-1, i) in the permutation:
		const unsigned& source = tour[i-1].second;
		const unsigned& destination = tour[i].second;

		distance += instance.getDistance(source, destination);
	}

	// Close the tour:
	const unsigned& last = tour.back().second;
	const unsigned& first = tour.front().second;
	distance += instance.getDistance(last, first);
}

TSPSolver::~TSPSolver() {
}

unsigned TSPSolver::getTourDistance() const { return distance; }

std::list< unsigned > TSPSolver::getTour() const {
	std::list< unsigned > tourSequence;

	for(unsigned i = 0; i < tour.size(); ++i) { tourSequence.push_back(tour[i].second); }

	return tourSequence;
}

