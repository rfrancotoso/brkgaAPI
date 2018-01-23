/**
 * Population.cpp
 *
 * For details, see Population.h
 *
 * Created on : Jun 21, 2010 by rtoso
 * Last update: Mar 15, 2013 by rtoso
 * Authors    : Rodrigo Franco Toso <rtoso@cs.rutgers.edu>
 *              Mauricio G.C. Resende <mgcr@research.att.com>
 * Copyright 2010, 2011 Rodrigo Franco Toso and Mauricio G.C. Resende.
 * 
 * This file is part of the BRKGA API.
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

#include "Population.h"

Population::Population(const Population& pop) :
		population(pop.population),
		fitness(pop.fitness) {
}

Population::Population(const unsigned n, const unsigned p) :
		population(p, std::vector< double >(n, 0.0)), fitness(p) {
	if(p == 0) { throw std::range_error("Population size p cannot be zero."); }
	if(n == 0) { throw std::range_error("Chromosome size n cannot be zero."); }
}

Population::~Population() {
}

unsigned Population::getN() const {
	return population[0].size();
}

unsigned Population::getP() const {
	return population.size();
}

double Population::getBestFitness() const {
	return getFitness(0);
}

double Population::getFitness(unsigned i) const {
	#ifdef RANGECHECK
		if(i >= getP()) { throw std::range_error("Invalid individual identifier."); }
	#endif
	return fitness[i].first;
}

const std::vector< double >& Population::getChromosome(unsigned i) const {
	#ifdef RANGECHECK
		if(i >= getP()) { throw std::range_error("Invalid individual identifier."); }
	#endif
	
	return population[ fitness[i].second ];
}

std::vector< double >& Population::getChromosome(unsigned i) {
	#ifdef RANGECHECK
		if(i >= getP()) { throw std::range_error("Invalid individual identifier."); }
	#endif
	
	return population[ fitness[i].second ];
}

void Population::setFitness(unsigned i, double f) {
	fitness[i].first = f;
	fitness[i].second = i;
}

void Population::sortFitness() {
	sort(fitness.begin(), fitness.end());
}

double& Population::operator()(unsigned chromosome, unsigned allele) {
	return population[chromosome][allele];
}

std::vector< double >& Population::operator()(unsigned chromosome) {
	return population[chromosome];
}