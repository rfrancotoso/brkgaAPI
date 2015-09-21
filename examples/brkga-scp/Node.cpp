/*
 * TripletNode.cpp
 *
 *  Created on: Sep 24, 2010
 *      Author: rtoso
 */

#include "Node.h"

Node::Node(Node& node) : row(node.row), column(node.column), 
		up(node.up), down(node.down), right(node.right) {
}

Node::Node(const unsigned r, const unsigned c) : row(r), column(c),
	up(0), down(0), right(0) {
}

Node::~Node() { up = down = right = 0; }

Node& Node::operator=(const Node& other) {
	if(this != &other) {
        row = other.row;
		column = other.column;
		
		up = other.up;
		down = other.down;
		right = other.right;
    }

    return *this;
}
