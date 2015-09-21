/**
 * Main method.
 *
 * Command line parameters, to be entered in the order listed below:
 *     - seed
 *     - stopping rule & argument X: "0" to stop after X generations;
 *                                   "1" to stop when target fitness X is reached;
 *                                   "2" to stop when X generations have passed without improvement
 *     - instance file, following the OR-Library format.
 *
 * Configuration file parameters (must be supplied in the order defined below):
 *     - % of population in elite set
 *     - % of population in mutant set
 *     - probability of inheriting each allele from elite parent during mating
 *     - number of independent populations
 *     - number of threads to perform parallel decoding
 *     - frequency at which elite chromosome from each population are exchanged
 *     - number of chromosomes copied from each population into the others during synchronization
 *
 * Automatically set parameters:
 *     - Size of each population = 10n, where n is the number of rows in the set-covering instance
 *
 * Authors: Rodrigo F. Toso <rtoso@cs.rutgers.edu>
 *          Mauricio G.C. Resende <mgcr@research.att.com>
 */

#include <string>
#include <limits>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "brkgaAPI/BRKGA.h"
#include "brkgaAPI/MTRand.h"
#include "SetCoveringDecoder.h"
#include "SetCoveringSolution.h"

enum StopRule { GENERATIONS = 0, TARGET, IMPROVEMENT };

int main(int argc, char* argv[]) {
	using std::cout;
	using std::cerr;
	using std::endl;
	using std::string;
	using std::ifstream;

	// First read parameters from command line:
	if(argc < 5) {
		cerr << "usage: " << argv[0]
		     << " seed stop-rule stop-arg path-to-instance [-verbose]" << endl;
		return -1;
	}

	// Parameters set from command line:
	const long seed = atoi(argv[1]);					// RNG seed
	const unsigned stopRule = StopRule(atoi(argv[2]));	// stopping rule
	const unsigned stopArg = atoi(argv[3]);				// argument to stopping rule
	const string instanceFile = argv[4];					// instance file
	const bool verbose = (argc > 5);				// verbose mode?

	// Next, open algorithm configuration and test:
	ifstream fin("algorithm.conf", std::ios::in);
	if(!fin) {
		cerr << "Cannot find configuration file 'algorithm.conf'" << endl;
		return -1;
	}
	fin.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);

	// Parameters set from file 'algorithm.conf':
	double pe;			// % of elite items in the population
	double pm;			// % of mutants introduced at each generation
	double rhoe;		// prob of inheriting each allele from elite parent
	unsigned K;			// number of independent populations
	unsigned MAXT;	// number of threads in parallel decoding
	unsigned X_INTVL;			// frequency at which elite chromosomes from each population are exchanged
	unsigned X_NUMBER;			// number of elite chromosomes to obtain from each population

	try { fin >> pe >> pm >> rhoe >> K >> MAXT >> X_INTVL >> X_NUMBER; }
	catch(ifstream::failure& e) {
		cerr << "Failure when reading configfile: " << e.what() << endl;
		return -1;
	}
	fin.close();

	// Now initialize the RNG, decoder & algorithm and run:
	try {
		MTRand rng(seed);
		SetCoveringDecoder decoder(instanceFile.c_str());
		BRKGA< SetCoveringDecoder, MTRand > algorithm(decoder.getNColumns(),
				10 * decoder.getNRows(), pe, pm, rhoe, decoder, rng, K, MAXT);

		unsigned long iteration = 0;
		unsigned long lastUpdate = 0;
		double bestFitness = std::numeric_limits< double >::max();

		if(verbose) {
			string mode = "for #generations = ";
			if(stopRule == TARGET) { mode = "for target = "; }
			else if(stopRule == IMPROVEMENT) { mode = "until no improvement after #generations = "; }
			cout << argv[0] << ": instance " << argv[1] << " has " << decoder.getNRows()
					<< " rows to be covered with " << decoder.getNColumns() << " columns; running "
					<< mode << stopArg << "..." << endl;
		}

		bool run = true;
		while(run) {
			// Evolution:
			algorithm.evolve();

			// Elite-exchange:
			if(K > 1 && X_INTVL > 0 && iteration > 0 && iteration % X_INTVL == 0) {
				algorithm.exchangeElite(X_NUMBER);

				if(verbose) {
					cout << "Exchanged " << X_NUMBER << " solutions from each population at iteration "
							<< iteration << "; best so far: " << algorithm.getBestFitness() << endl;
				}
			}

			// Update runtime data:
			if(algorithm.getBestFitness() < bestFitness) {
				bestFitness = algorithm.getBestFitness();
				lastUpdate = iteration;
			}

			// Time to stop?
			switch(stopRule) {
			case GENERATIONS:
				if(iteration >= stopArg) { run = false; }
				break;

			case TARGET:
				if(bestFitness <= stopArg) { run = false; }
				break;

			case IMPROVEMENT:
				if(iteration - lastUpdate >= stopArg) { run = false; }
				break;
			}

			++iteration;	// Prepare next iteration
		}

		std::vector< double > bestChromosome(algorithm.getBestChromosome());
		SetCoveringSolution best(bestChromosome, true, true, false, 0.5);
		if(! decoder.verify(best.getSelectedColumns())) {
			cerr << "WARNING: Best solution could NOT be verified!" << endl;
		}

		if(verbose) {
			cout << "Best fitness: " << bestFitness
				<< "\nIterations: " << iteration
				<< "\nBest solution:";

			unsigned counter = 0;
			for(unsigned j = 0; j < best.getSelectedColumns().size(); ++j) {
				bool val = best.getSelectedColumns()[j];
				if(val) { cout << " " << j; ++counter; }
			}
			cout << endl;
		}
		else { cout << iteration << endl; }
	}
	catch(std::range_error& e) {
		cerr << "Runtime error: " << e.what() << endl;
		return -2;
	}
	catch(std::exception& e) {
		cerr << "Exception: " << e.what() << endl;
		return -3;
	}

	return 0;
}
