/*
 * SteinerTripleDecoder.cpp
 *
 *  Created on: Sep 24, 2010
 *      Author: rtoso
 */

#include "SetCoveringDecoder.h"

unsigned SetCoveringDecoder::nrows;								// Number of rows
unsigned SetCoveringDecoder::ncolumns;							// Number of columns
std::vector< Node* > SetCoveringDecoder::rows;					// First node of each row
std::vector< Node* > SetCoveringDecoder::columns;					// First node of each column
std::vector< double > SetCoveringDecoder::columnCosts;				// Cost of using each column
std::vector< unsigned > SetCoveringDecoder::rowsCoveredByColumn;	// Rows that each column covers
std::vector< std::pair< double, unsigned > > SetCoveringDecoder::sortedColumnCosts;	// Decreasing

SetCoveringDecoder::SetCoveringDecoder(const char* filename) {
	std::ifstream in(filename, std::ios::in);
	if(!in) { throw std::runtime_error("Unable to read instance from standard input."); }

	// Read basic information:
	in >> nrows >> ncolumns;

	// Allocate memory based on the problem's dimensions:
	rows.resize(nrows, 0);
	columns.resize(ncolumns, 0);
	columnCosts.resize(ncolumns, 0);
	rowsCoveredByColumn.resize(ncolumns, 0);

	// Read the column's costs:
	for(unsigned i = 0; i < ncolumns; ++i) {
		double c = 0.0;
		in >> c;
		columnCosts[i] = c;
		sortedColumnCosts.push_back(std::pair< double, unsigned >(c, i));
	}

	// Sort column costs by cost:
	std::sort(sortedColumnCosts.rbegin(), sortedColumnCosts.rend());

	// Read each row:
	unsigned numcol = 0;	// Number of columns that cover row i below
	for(unsigned i = 0; i < nrows; ++i) {
		// Read number of columns that cover row 'i':
		in >> numcol;

		// Read each column covering line 'i', _offsetting_ to start at 0, and allocate nodes:
		unsigned c = 0;
		in >> c;
		Node* head = new Node(i, --c);
		Node* tail = head;
		for(unsigned j = 1; j < numcol; ++j) {
			in >> c;
			Node* curr = new Node(i, --c);
			tail->right = curr;
			tail = curr;
		}

		tail->right = head;	// close the circular list

		// Insert triple into 'columns' and 'rows':
		insertRow(head);
	}
}

SetCoveringDecoder::~SetCoveringDecoder() {
	for(unsigned i = 0; i < nrows; ++i) { deleteRow(i); }
}

double SetCoveringDecoder::decode(std::vector< double >& chromosome) const {
	SetCoveringSolution solution(chromosome, false, false, false, 0.5);
	bool coverChangedSolution = solution.greedyCover();
	bool uncover1ChangedSolution = solution.greedyUncover();
	bool oneOPTChangedSolution = solution.oneOPT();
	bool uncover2ChangedSolution = solution.greedyUncover();
	if(coverChangedSolution || uncover1ChangedSolution || oneOPTChangedSolution ||
			uncover2ChangedSolution) {
		// Columns were unselected; check if chromosome should be changed too:
		const std::vector< bool >& selectedCols = solution.getSelectedColumns();
		for(unsigned i = 0; i < chromosome.size(); ++i) {
			if((chromosome[i] >= 0.5 && selectedCols[i] == false) ||
					(chromosome[i] < 0.5 && selectedCols[i] == true)) {
				chromosome[i] = 1.0 - chromosome[i];
			}
		}
	}

	return solution.getCost();
}

bool SetCoveringDecoder::verify(const std::vector< bool >& cover) const {
	unsigned coveredRows = 0;
	std::vector< unsigned > rowsCovered(nrows);
	for(unsigned i = 0; i < cover.size(); ++i) {
		if(!cover[i]) { continue; }

		for(Node* ptr = columns[i]; ptr != 0; ptr = ptr->down) {
			if(++rowsCovered[ptr->row] == 1) { ++coveredRows; }
		}
	}

	return (coveredRows == nrows);
}

unsigned SetCoveringDecoder::getNRows() const {
	return nrows;
}

unsigned SetCoveringDecoder::getNColumns() const {
	return ncolumns;
}

bool SetCoveringDecoder::deleteRow(const unsigned i) {
	if(rows[i] == 0) { return false; }

	// This is the head of the CLL:
	Node* head = rows[i];

	// Remove from 'rows':
	rows[i] = 0;

	// Fix the doubly-linked lists:
	for(Node* ptr = head->right; ptr != head; ptr = ptr->right) { removeFromColumn(ptr); }
	removeFromColumn(head);

	// Deallocate memory and say goodbye:
	Node* curr = head->right;
	Node* next = curr->right;
	while(next != head) {
		delete curr;
		curr = next;
		next = next->right;
	}

	delete head;
	return true;
}

void SetCoveringDecoder::removeFromColumn(Node* node) {
	if(node == 0) { return ; }

	// Remove from head of DLL:
	if(columns[node->column] == node) {
		columns[node->column] = node->down;
		if(node->down != 0) { node->down->up = 0; }
	}
	else {
		// General case:
		node->up->down = node->down;
		if(node->down != 0) { node->down->up = node->up; }
	}

	// Update counter:
	--rowsCoveredByColumn[node->column];
}

void SetCoveringDecoder::insertRow(Node* head) {
	// Insert into 'rows':
	rows[head->row] = head;

	// Insert into 'columns':
	Node* ptr = head;
	do {
		insertIntoColumn(ptr);
		ptr = ptr->right;
	} while(ptr != head);
}

void SetCoveringDecoder::insertIntoColumn(Node* node) {
	// Insert into empty DLL:
	if(columns[node->column] == 0) { columns[node->column] = node; node->up = 0; node->down = 0; }
	else {
		// Insert into head of DLL:
		Node* head = columns[node->column];
		head->up = node;
		node->up = 0;
		node->down = head;

		columns[node->column] = node;	// Update head
	}

	++rowsCoveredByColumn[node->column];
}
