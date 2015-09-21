/*
 * SteinerTripleSolution.h
 *
 *  Created on: Oct 2, 2010
 *      Author: rtoso
 */

#ifndef SETCOVERINGSOLUTION_H
#define SETCOVERINGSOLUTION_H

#include <list>
#include <vector>
#include "Node.h"
#include "BinaryHeap.h"
#include "SetCoveringDecoder.h"

class SetCoveringSolution {
public:
	explicit SetCoveringSolution(const std::vector< double >& chromosome,
			const bool runCover, const bool runUncover, const bool runOneOPT, double cutoff);
	~SetCoveringSolution();

	// Greedy heuristic to open extra columns so as to make *this feasible
	// Returns: true if the solution changed
	bool greedyCover();

	// Greedy heuristic to iterate over all selected columns un-selecting those not needed
	// Returns: true if the solution changed
	bool greedyUncover();

	// 1-OPT local search: iterate over the selected columns in decreasing cost order, trying
	// to exchange them for columns with lesser cost. Run this after calling greedyUncover()
	// on top of a feasible solution.
	bool oneOPT();

	// Algorithm to open a new column while updating internals and the heap, if supplied
	void openColumn(const unsigned column, BinaryHeap< double >** refHeap);

	// Algorihm to close a column:
	void closeColumn(const unsigned column);

	// Is *this feasible?
	bool isFeasible() const;

	// Cost of this solution:
	double getCost() const;

	// Returns the number of opened columns
	unsigned getOpenedColumns() const;

	// Returns a vector s.t. for every column i, [i] == true if i is opened; false otherwise
	const std::vector< bool >& getSelectedColumns() const;

private:
	// Cost:
	double cost;
	// Number of covered rows:
	unsigned coveredRows;
	// Number of opened columns:
	unsigned openedColumns;
	// Number of opened columns covering each row:
	std::vector< unsigned > colsCoveringRow;
	// True if column is in the solution:
	std::vector< bool > selectedColumns;
	// Number of uncovered rows that'll get covered by each column:
	std::vector< unsigned > rowsCoveredByCol;
};

#endif
