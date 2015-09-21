/*
 * TSPInstance.cpp
 *
 *  Created on: Mar 16, 2013
 *      Author: Rodrigo
 */

#include "TSPInstance.h"

TSPInstance::TSPInstance(const std::string& instanceFile) throw(TSPInstance::Error) :
		name(""), comment(""), problemType(""), edgeWeightType(""),
		nNodes(0), nodeCoords() {
	std::ifstream fin(instanceFile.c_str());
	if(! fin) { throw Error("TSPInstance: Cannot open input file."); }

	std::string line;
	std::string token;

	// WARNING: the code below assumes an ordered input file following a280.tsp
	//          it will not work with all instances in the TSPLIB.
	try {
		std::getline(fin, line);
		readName(line);

		std::getline(fin, line);
		readComment(line);

		std::getline(fin, line);
		readProblemType(line);

		std::getline(fin, line);
		readDimension(line);

		std::getline(fin, line);
		readEdgeWeightType(line);

		std::getline(fin, line);
		if(line != "NODE_COORD_SECTION") {
			throw Error("Cannot recognize instance: NODE_COORD_SECTION not where it should be.");
		}

		std::getline(fin, line);
		while(! isEOF(line)) {
			readNodeCoords(line);

			std::getline(fin, line);
		}

	}
	catch(const Error& error) { throw error; }
}

TSPInstance::~TSPInstance() { }

unsigned TSPInstance::getNumNodes() const { return nNodes; }
const std::string& TSPInstance::getName() const { return name; }
const std::string& TSPInstance::getComment() const { return comment; }
const std::string& TSPInstance::getProblemType() const { return problemType; }
const std::string& TSPInstance::getEdgeWeightType() const { return edgeWeightType; }

unsigned TSPInstance::getDistance(unsigned i, unsigned j) const {
	const double x2 = std::pow(nodeCoords[i].getX() - nodeCoords[j].getX(), 2.0);
	const double y2 = std::pow(nodeCoords[i].getY() - nodeCoords[j].getY(), 2.0);

	return std::floor((x2 + y2) + 0.5);
}

void TSPInstance::readName(const std::string& line) throw(TSPInstance::Error) {
	if(line.find("NAME") == std::string::npos) {
		throw Error("Cannot recognize instance: NAME not where it should be.");
	}

	name = line.substr(line.find(":") + 1);
	trim(name);	// this instance format is horrible!
}

void TSPInstance::readComment(const std::string& line) throw(TSPInstance::Error) {
	if(line.find("COMMENT") == std::string::npos) {
		throw Error("Cannot recognize instance: NAME not where it should be.");
	}

	comment = line.substr(line.find(":") + 1);
	trim(comment);	// this instance format is horrible!
}

void TSPInstance::readProblemType(const std::string& line) throw(TSPInstance::Error) {
	if(line.find("TYPE") == std::string::npos) {
		throw Error("Cannot recognize instance: NAME not where it should be.");
	}

	problemType = line.substr(line.find(":") + 1);
	trim(problemType);	// this instance format is horrible!

	if(problemType != "TSP") { throw Error("Cannot work on instance type " + problemType); }
}

void TSPInstance::readDimension(const std::string& line) throw(TSPInstance::Error) {
	if(line.find("DIMENSION") == std::string::npos) {
		throw Error("Cannot recognize instance: NAME not where it should be.");
	}

	const std::string dimStr = line.substr(line.find(":") + 1);
	nNodes = std::atoi(dimStr.c_str());

	nodeCoords.resize(nNodes);
}

void TSPInstance::readEdgeWeightType(const std::string& line) throw(TSPInstance::Error) {
	if(line.find("EDGE_WEIGHT_TYPE") == std::string::npos) {
		throw Error("Cannot recognize instance: NAME not where it should be.");
	}

	edgeWeightType = line.substr(line.find(":") + 1);
	trim(edgeWeightType);	// this instance format is horrible!

	if(edgeWeightType != "EUC_2D") { throw Error("Cannot only work with instance type EUC_2D."); }
}

void TSPInstance::readNodeCoords(const std::string& line) throw(TSPInstance::Error) {
	// Assumes a 2D instance:
	std::istringstream sin(line);

	unsigned nodeId;
	double x;
	double y;

	sin >> nodeId >> x >> y;

	if(nodeId == 0 || nodeId > nNodes) { throw Error("Node coordinate invalid."); }
	nodeCoords[nodeId - 1] = Coord2D(x, y);
}

bool TSPInstance::isEOF(const std::string& line) const {
	if(line.find("EOF") == std::string::npos) { return false; }
	return true;
}

void TSPInstance::trim(std::string& str) const {
	// trim white spaces at the beginning:
	unsigned begin = 0;
	while(begin < str.size() && str[begin] == ' ') { ++begin; }

	unsigned end = str.size() - 1;
	while(end > 0 && str[end] == ' ') { --end; }

	str = str.substr(begin, end - begin + 1);
}

