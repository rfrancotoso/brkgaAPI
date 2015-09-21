/*
 * TripletNode.h
 *
 *  Created on: Sep 24, 2010
 *      Author: rtoso
 */

#ifndef TRIPLETNODE_H
#define TRIPLETNODE_H

class Node {
public:
	Node(Node& node);
	Node(const unsigned row, const unsigned column);
	virtual ~Node();
	
	Node& operator=(const Node&rhs);

	unsigned row;
	unsigned column;

	Node* up;
	Node* down;
	Node* right;
};

#endif
