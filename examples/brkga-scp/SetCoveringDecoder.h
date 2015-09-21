/*
 * SteinerTripleDecoder.h
 *
 *  Created on: Sep 24, 2010
 *      Author: rtoso
 */

#ifndef SETCOVERINGDECODER_H
#define SETCOVERINGDECODER_H

#include <omp.h>
#include <istream>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "Node.h"
#include "SetCoveringSolution.h"

class SetCoveringDecoder {
	friend class SetCoveringSolution;

public:
	SetCoveringDecoder(const char* filename);
	~SetCoveringDecoder();

	double decode(std::vector< double >& chromosome) const;
	bool verify(const std::vector< bool >& cover) const;

	unsigned getNRows() const;
	unsigned getNColumns() const;

private:
	// Instance structure:
	static unsigned nrows;								// Number of rows
	static unsigned ncolumns;							// Number of columns
	static std::vector< Node* > rows;					// Pointer to the first node of each row
	static std::vector< Node* > columns;				// Pointer to the first node of each column
	static std::vector< double > columnCosts;			// Cost of adding each column
	static std::vector< unsigned > rowsCoveredByColumn;	// Number of rows that each column covers
	static std::vector< std::pair< double, unsigned > > sortedColumnCosts;	// Sorted costs & column

	// No copy or assignment allowed
	SetCoveringDecoder(const SetCoveringDecoder& source);
	SetCoveringDecoder& operator=(const SetCoveringDecoder& source);

	// Deletes row i while also re-adjusting the columns & counters (also frees memory)
	bool deleteRow(const unsigned i);

	// Auxiliary method for deleteRow() -- detach 'node' from doubly linked list (columns):
	void removeFromColumn(Node* node);

	// Inserts a row given as a circular linked list, while adjusting both rows and columns:
	void insertRow(Node* head);

	// Auxiliary method for insertRow() -- attach 'node' into doubly linked list (columns):
	void insertIntoColumn(Node* node);
};

#endif
