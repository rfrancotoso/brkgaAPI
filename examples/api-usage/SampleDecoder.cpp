/*
 * SampleDecoder.cpp
 *
 * For more information, see SampleDecoder.h
 *
 * Created on : Nov 17, 2011 by rtoso
 * Authors    : Rodrigo Franco Toso <rtoso@cs.rutgers.edu>
 *              Mauricio G.C. Resende <mgcr@research.att.com>
 * Copyright 2010, 2011 Rodrigo Franco Toso and Mauricio G.C. Resende.
 * 
 * This file is part of the BRKGA API.
 *
 * The BRKGA API is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The BRKGA API is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the BRKGA API. If not, see <http://www.gnu.org/licenses/>.
 */

#include "SampleDecoder.h"

SampleDecoder::SampleDecoder() { }

SampleDecoder::~SampleDecoder() { }

// Runs in O(n \log n):
double SampleDecoder::decode(const std::vector< double >& chromosome) const {
	double myFitness = 0.0;
	typedef std::pair< double, unsigned > ValueKeyPair;
	std::vector< ValueKeyPair > rank(chromosome.size());

	for(unsigned i = 0; i < chromosome.size(); ++i) {
		rank[i] = ValueKeyPair(chromosome[i], i);
		myFitness += (double(i + 1) * chromosome[i]);
	}

	// Here we sort 'permutation', which will then produce a permutation of [n]
	// stored in ValueKeyPair::second:
	std::sort(rank.begin(), rank.end());

	// permutation[i].second is in {0, ..., n - 1}; a permutation can be obtained as follows
	std::list< unsigned > permutation;
	for(std::vector< ValueKeyPair >::const_iterator i = rank.begin(); i != rank.end(); ++i) {
		permutation.push_back(i->second);
	}

	// Return the fitness:
	return myFitness;
}
