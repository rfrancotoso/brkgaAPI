/*
 * TSPInstance.h
 *
 * Reads an instance from TSPLIB (Symmetric TSP).
 *
 * Here's the URL: http://www.iwr.uni-heidelberg.de/groups/comopt/software/TSPLIB95/tsp/
 *
 * Here's the format:
 *
 * NAME : a280
 * COMMENT : drilling problem (Ludwig)
 * TYPE : TSP
 * DIMENSION: 280
 * EDGE_WEIGHT_TYPE : EUC_2D
 * NODE_COORD_SECTION
 * 1 288 149
 * 2 288 129
 * 3 270 133
 * 4 256 141
 * ...
 * EOF
 *
 *  Created on: Mar 16, 2013
 *      Author: Rodrigo
 */

#ifndef TSPINSTANCE_H
#define TSPINSTANCE_H

#include <cmath>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>

class TSPInstance {
public:
	typedef std::runtime_error Error;

	TSPInstance(const std::string& instanceFile) throw(Error);
	virtual ~TSPInstance();

	// Getters:
	unsigned getNumNodes() const;
	const std::string& getName() const;
	const std::string& getComment() const;
	const std::string& getProblemType() const;
	const std::string& getEdgeWeightType() const;

	// Returns the distance from node i to node j:
	unsigned getDistance(unsigned i, unsigned j) const;

private:
	std::string name;
	std::string comment;
	std::string problemType;
	std::string edgeWeightType;

	unsigned nNodes;

	class Coord2D {
	public:
		Coord2D() : x(0.0), y(0.0) { }
		Coord2D(double _x, double _y) : x(_x), y(_y) {}

		double getX() const { return x; }
		double getY() const { return y; }

	private:
		double x;
		double y;
	};

	std::vector< Coord2D > nodeCoords;

	void readName(const std::string& line) throw(Error);
	void readComment(const std::string& line) throw(Error);
	void readProblemType(const std::string& line) throw(Error);
	void readDimension(const std::string& line) throw(Error);
	void readEdgeWeightType(const std::string& line) throw(Error);

	void readNodeCoords(const std::string& line) throw(Error);
	bool isEOF(const std::string& line) const;
	void trim(std::string& str) const;
};

#endif
