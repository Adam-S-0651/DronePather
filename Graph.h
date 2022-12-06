#pragma once
#include <unordered_map>
#include <iostream>
#include "Node.h"
#include "Hasher.h"

using namespace std;
class Graph
{
	public:
		Graph(unsigned int& numNodes, unsigned int& maxEdges, unsigned int& maxXYZ);
		tuple<vector<unsigned int>, double, unsigned long> dijkstrasPath(unsigned int start, unsigned int end);
		tuple<vector<unsigned int>, double, unsigned long> aPath(unsigned int start, unsigned int end);
		void printGraph();
		void runPathfinder(char c, int from, int to);

	private:
		// Class variables
		unordered_map<unsigned int, unordered_map<unsigned int, double>> graph3D;
		unordered_map<unsigned int, Node> identifiers;
		unsigned int numNodes, maxEdges, maxXYZ;

		// Functions for generating the graph
		double distanceFinder(Node& start, Node& end);
		unsigned int randomGenerator(unsigned int rangeFrom, unsigned int rangeTo);
		unsigned int randomGenerator(unsigned int rangeTo);
		void makeNodes();
		void makeEdges();

		// Convenience functions to save a few characters
		Node& nodeFromIter(unordered_map<unsigned int, unordered_map<unsigned int, double>>::iterator it);
		Node& nodeFromIter(unordered_map<unsigned int, double>::iterator it);
};