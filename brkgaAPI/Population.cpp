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