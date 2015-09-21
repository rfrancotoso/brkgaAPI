/*
 * SteinerTripleSolution.cpp
 *
 *  Created on: Oct 2, 2010
 *      Author: rtoso
 */

#include "SetCoveringSolution.h"

SetCoveringSolution::SetCoveringSolution(const std::vector< double >& chromosome,
		const bool runCover, const bool runUncover, const bool runOneOPT, const double cutoff) :
		cost(0.0),
		coveredRows(0),
		openedColumns(0),
		colsCoveringRow(SetCoveringDecoder::nrows, 0),
		selectedColumns(SetCoveringDecoder::ncolumns, false),
		rowsCoveredByCol(SetCoveringDecoder::rowsCoveredByColumn) {
	// First, open all columns indicated by the chromosome:
	for(unsigned j = 0; j < chromosome.size(); ++j) {
		if(chromosome[j] < cutoff || rowsCoveredByCol[j] == 0) { continue; }
		openColumn(j, 0);	// Open it
	}

	if(runCover && isFeasible() == false) { greedyCover(); }

	if(runUncover) { greedyUncover(); }

	if(runOneOPT) { oneOPT(); }
}

SetCoveringSolution::~SetCoveringSolution() { }

bool SetCoveringSolution::isFeasible() const {
	return (coveredRows == SetCoveringDecoder::nrows);
}

double SetCoveringSolution::getCost() const { return cost; }

unsigned SetCoveringSolution::getOpenedColumns() const {
	return (isFeasible() ? openedColumns : SetCoveringDecoder::ncolumns);
}

const std::vector< bool >& SetCoveringSolution::getSelectedColumns() const {
	return selectedColumns;
}

bool SetCoveringSolution::greedyCover() {
	if(coveredRows == SetCoveringDecoder::nrows) { return false; }

	// Initialize heap with columnCount values:
	BinaryHeap< double >* heap = new BinaryHeap< double >(SetCoveringDecoder::ncolumns);
	for(unsigned j = 0; j < SetCoveringDecoder::ncolumns; ++j) {
		if(rowsCoveredByCol[j] > 0) {
			heap->insert(j, - double(rowsCoveredByCol[j] / SetCoveringDecoder::columnCosts[j]));
		}
	}

	while(coveredRows < SetCoveringDecoder::nrows) {
		const unsigned greedyCol = heap->extractMin();	// Get best column from heap

		openColumn(greedyCol, &heap);	// Open it
	}

	delete heap;
	return isFeasible();
}

bool SetCoveringSolution::greedyUncover() {
	bool improved = false;
	for(std::vector< std::pair< double, unsigned > >::const_iterator
			p = SetCoveringDecoder::sortedColumnCosts.begin();
			p != SetCoveringDecoder::sortedColumnCosts.end(); ++p) {
		const unsigned i = p->second;
		if(selectedColumns[i] == false) { continue; }	// Only proceed if column was selected

		// check if this column can be eliminated:
		bool success = true;
		for(Node* ptr = SetCoveringDecoder::columns[i]; ptr != 0; ptr = ptr->down) {
			if(colsCoveringRow[ptr->row] <= 1) { success = false; break; }
		}

		if(success) { improved = true; closeColumn(i); }
	}

	return improved;
}

bool SetCoveringSolution::oneOPT() {
	// Iterate over the selected columns in decreasing order of cost:
	bool improved = false;
	for(unsigned i = 0; i < SetCoveringDecoder::ncolumns; ++i) {
		const double& costToLeave = SetCoveringDecoder::sortedColumnCosts[i].first;
		const unsigned& columnToLeave = SetCoveringDecoder::sortedColumnCosts[i].second;

		// Only proceed if column was selected; if not, continue...
		if(selectedColumns[columnToLeave] == false) { continue; }

		// Column 'columnToLeave' with cost = 'costToLeave', is a candidate for leaving...
		// We first build a list of the rows affected by the removal of such:
		std::list< unsigned > uncoveredRows;
		for(Node* ptr = SetCoveringDecoder::columns[columnToLeave]; ptr != 0; ptr = ptr->down) {
			if(colsCoveringRow[ptr->row] == 1) { uncoveredRows.push_back(ptr->row); }
		}

		if(uncoveredRows.size() == 0) {
			closeColumn(columnToLeave);
			continue;
		}

		// We'll now search for a column covering _all_ rows in 'uncoveredRows' with a better cost:
		for(unsigned j = i + 1; j < SetCoveringDecoder::ncolumns; ++j) {
			const double& costToEnter = SetCoveringDecoder::sortedColumnCosts[j].first;
			const unsigned& columnToEnter = SetCoveringDecoder::sortedColumnCosts[j].second;

			// Only proceed if column is not selected _and_ its cost is strictly better:
			if(costToEnter >= costToLeave || selectedColumns[columnToEnter] == true) { continue; }

			// Does this column cover the rows left uncovered after the removal of columnToLeave?
			unsigned willCover = 0;
			for(Node* ptr = SetCoveringDecoder::columns[columnToEnter]; ptr != 0; ptr = ptr->down) {
				std::list< unsigned >::iterator pos = std::find(uncoveredRows.begin(),
						uncoveredRows.end(), ptr->row);
				if(pos == uncoveredRows.end()) { break; }
				else { ++willCover; }
			}

			// If so, exchange and break out of the loop:
			if(willCover == uncoveredRows.size()) {
				closeColumn(columnToLeave);
				openColumn(columnToEnter, 0);
				improved = true;
				break;
			}
		}
	}

	return improved;
}

inline void SetCoveringSolution::openColumn(const unsigned column, BinaryHeap< double >** ptrHeap) {
	// Process current row, being covered by col. 'column':
	for(Node* ptr = SetCoveringDecoder::columns[column]; ptr != 0; ptr = ptr->down) {
		// Update 'rowsCoveredByCol' if this row is being covered for the first time:
		if(++colsCoveringRow[ptr->row] == 1) {
			++coveredRows;

			// Now
			Node* head = SetCoveringDecoder::rows[ptr->row];
			Node* curr = head;
			do {
				--rowsCoveredByCol[curr->column];

				if(ptrHeap != 0) {
					(*ptrHeap)->increaseKey(curr->column,
							- double(rowsCoveredByCol[curr->column]
							         / SetCoveringDecoder::columnCosts[curr->column]));
				}
				curr = curr->right;
			} while(curr != head);
		}
	}

	cost += SetCoveringDecoder::columnCosts[column];
	selectedColumns[column] = true;
	rowsCoveredByCol[column] = 0;
	++openedColumns;
}

inline void SetCoveringSolution::closeColumn(const unsigned column) {
	for(Node* ptr = SetCoveringDecoder::columns[column]; ptr != 0; ptr = ptr->down) {
		if(--colsCoveringRow[ptr->row] == 0) { --coveredRows; }
	}

	--openedColumns;
	selectedColumns[column] = false;
	cost -= SetCoveringDecoder::columnCosts[column];
}
