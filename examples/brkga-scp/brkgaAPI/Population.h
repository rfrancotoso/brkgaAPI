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
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2018
 * Rodrigo Franco Toso (rfrancotoso@gmail.com) and
 * Mauricio G.C. Resende
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
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
