/**
 * Population.h
 *
 * Encapsulates a population of chromosomes represented by a vector of doubles. We don't decode
 * nor deal with random numbers here; instead, we provide private support methods to set the
 * fitness of a specific chromosome as well as access methods to each allele. Note that the BRKGA
 * class must have access to such methods, thus begin a friend. In terms of design, this class is
 * obviously tightly coupled with BRKGA, and was implemented just to remove unnecessary complexity
 * from the design of BRKGA.
 *
 * All public methods in this API *require* the fitness array to be sorted, and thus a call to
 * sortFitness() beforehand. Since this class is tightly coupled with BRKGA, rest assured: 
 * everything will work just fine with a Population obtained from BRKGA.
 *
 * Created on : Jun 21, 2010 by rtoso
 * Last update: Nov 15, 2010 by rtoso
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

#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <algorithm>
#include <exception>
#include <stdexcept>

class Population {
	template< class Decoder, class RNG >
	friend class BRKGA;

public:
	unsigned getN() const;	// Size of each chromosome
	unsigned getP() const;	// Size of population

	// These methods REQUIRE fitness to be sorted, and thus a call to sortFitness() beforehand
	// (this is done by BRKGA, so rest assured: everything will work just fine with BRKGA).
	// Returns the best fitness in this population:
	double getBestFitness() const;
	
	// Returns the fitness of chromosome i \in {0, ..., getP() - 1}
	double getFitness(unsigned i) const;
	
	// Returns (i+1)-th best chromosome, where i = 0 is the best and i = getP() - 1 is the worst:
	const std::vector< double >& getChromosome(unsigned i) const;

private:
	Population(const Population& other);
	Population(unsigned n, unsigned p);
	~Population();

	std::vector< std::vector< double > > population;		// Population as vectors of prob.
	std::vector< std::pair< double, unsigned > > fitness;	// Fitness (double) of a each chromosome

	void sortFitness();									// Sorts 'fitness' by its first parameter
	void setFitness(unsigned i, double f);				// Sets the fitness of chromosome i
	std::vector< double >& getChromosome(unsigned i);	// Returns a chromosome

	double& operator()(unsigned i, unsigned j);		// Direct access to allele j of chromosome i
	std::vector< double >& operator()(unsigned i);	// Direct access to chromosome i
};

#endif
