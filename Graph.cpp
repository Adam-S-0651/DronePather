#include <random>
#include <unordered_set>
#include <queue>
#include <math.h>
#include <set>
#include "Graph.h"

// Constructor for the graph object
Graph::Graph(unsigned int& numNodes, unsigned int& maxEdges, unsigned int& maxXYZ) {
	this->numNodes = numNodes;
	this->maxEdges = maxEdges;
	this->maxXYZ = maxXYZ;

	makeNodes();
	makeEdges();
}

// Randomly generates a number in the given range and returns it
unsigned int Graph::randomGenerator(unsigned int rangeFrom, unsigned int rangeTo) {
	// This was adapted from https://stackoverflow.com/questions/288739/generate-random-numbers-uniformly-over-an-entire-range
	random_device randomGen;
	mt19937 generator(randomGen());
	uniform_int_distribution<unsigned int> distr(rangeFrom, rangeTo);

	return distr(generator);
}

// Overloading for if the range is meant to start at 0
unsigned int Graph::randomGenerator(unsigned int rangeTo) {
	return randomGenerator((unsigned int)0, rangeTo);
}

// Makes all of the unique nodes for the graph
void Graph::makeNodes() {
	unsigned int index = 0;
	// This is the only time Hasher is used to make the insertion fast
	unordered_set<Node, Hasher> s;
	while (s.size() != numNodes) {
		Node temp(randomGenerator(maxXYZ), randomGenerator(maxXYZ), randomGenerator(maxXYZ));
		s.insert(temp);
	}
	for (auto it = s.begin(); it != s.end(); it++) {
		identifiers.insert(make_pair(index, *it));
		graph3D.insert(make_pair(index, unordered_map<unsigned int, double>{}));
		index++;
	}
}

// Assigns each node with a certain number of directed and weighted edges
void Graph::makeEdges() {
	//Assuming randomness in unordered_map, make a cycle to ensure connectedness
	auto it = graph3D.begin();
	while (it != graph3D.end()) {
		unsigned int temp = it->first;
		it++;
		// Create last link from last element in map to first
		if (it == graph3D.end()) {
			graph3D.begin()->second.insert(make_pair(temp, distanceFinder(identifiers.find(temp)->second, identifiers.find(graph3D.begin()->first)->second)));
		}
		else {
			it->second.insert(make_pair(temp, distanceFinder(identifiers.find(temp)->second, nodeFromIter(it))));
		}
	}

	// Iterates through every node in the map
	for (auto it = graph3D.begin(); it != graph3D.end(); it++) {
		// Determines how many edges the node will have
		int numEdges = randomGenerator(1, maxEdges);
		auto it2 = graph3D.begin();

		// Moves iterator by a random amount each attempt to add a new node with an edge
		while (it->second.size() != numEdges) {
			int numSteps = randomGenerator(numNodes);
			for (int i = 0; i < numSteps; i++) {
				it2++;
				// Makes sure that the iterator doesn't go out of bounds
				if (it2 == graph3D.end()) {
					it2 = graph3D.begin();
				}
			}
			// Checks to make sure that there isn't a self-connection
			if (!(it2->first == it->first)) {
				it->second.insert(make_pair(it2->first, distanceFinder(nodeFromIter(it), nodeFromIter(it2))));
			}
		}
	}
}

// Calculates distance (weight) of each edge
double Graph::distanceFinder(Node& start, Node& end) {
	return sqrt(pow((int)start.getX() - (int)end.getX(), 2) + pow((int)start.getY() - (int)end.getY(), 2) + pow((int)start.getZ() - (int)end.getZ(), 2) * 1.0);
}

// Prints out all of the graph's unique ID's for testing purposes
void Graph::printGraph() {
	unsigned int count = 0;
	for (auto it = graph3D.begin(); it != graph3D.end(); it++) {
		if (identifiers.find(it->first) != identifiers.end()) {
			Node temp = identifiers.find(it->first)->second;
			cout << "Node " << count << ": (" << temp.getX() << "," << temp.getY() << "," << temp.getZ() << ") /" << " Connected: ";
			for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
				cout << it2->first << " ";
			}
		}
		cout << endl;
		count++;
	}
}

// Call the wanted algorithm and print results
void Graph::runPathfinder(char c, int from, int to) {
	tuple<vector<unsigned int>, double, unsigned long> shortestPath;


	if (c == 'a') {
		// Placeholder call to nodes
		shortestPath = aPath(from, to);
	}
	else if (c == 'd') {
		shortestPath = dijkstrasPath(from, to);
	}

	cout << "The shortest path length from A to B is " << fixed << setprecision(2) << get<1>(shortestPath) << endl;
	cout << "The number of edges traversed is: " << get<2>(shortestPath) << endl;
	cout << "The path is as follows:" << endl;

	for (int i = get<0>(shortestPath).size() - 1; i >= 0; i--) {
		cout << get<0>(shortestPath).at(i) << endl;
	}
}

// Retrieves the desired node from the identifiers map
Node& Graph::nodeFromIter(unordered_map<unsigned int, unordered_map<unsigned int, double>>::iterator it) {
	return identifiers.find(it->first)->second;
}

// Overloaded version from above
Node& Graph::nodeFromIter(unordered_map<unsigned int, double>::iterator it) {
	return identifiers.find(it->first)->second;
}

// Dijkstra's Algorithm
tuple<vector<unsigned int>, double, unsigned long> Graph::dijkstrasPath(unsigned int start, unsigned int end) {
	// Decleare starting states
	vector<double> pathLength(graph3D.size(), INFINITY);
	vector<int> prevNode(graph3D.size(), start);
	priority_queue<pair<double, unsigned int>> leftover;
	unsigned long count = 0;

	// Set up initial values for the priority queue
	leftover.push(make_pair(0.0, start));
	for (auto it = graph3D.begin(); it != graph3D.end(); it++) {
		if (it->first != start) {
			leftover.push(make_pair(INFINITY, it->first));
		}
	}
	// Initial distance to first node will always be 0;
	pathLength.at(start) = 0.0;

	// Dijkstras which will find the shortest path to every vertex from start vertex
	while (!leftover.empty()) {
		unsigned int curr = leftover.top().second;
		leftover.pop();

		// Cycle through the connected edges
		for (auto it = graph3D.find(curr)->second.begin(); it != graph3D.find(curr)->second.end(); it++) {
			unsigned int vertex = it->first;
			double dist = it->second;
			count++;

			// Relaxation for all edges involved
			if (pathLength.at(vertex) > pathLength.at(curr) + dist) {
				pathLength.at(vertex) = pathLength.at(curr) + dist;
				leftover.push(make_pair(pathLength.at(vertex), vertex));
				prevNode.at(vertex) = curr;
			}
		}
	}

	// Makes a vector of the path taken to get to selected node in reverse order (last->first node)
	unsigned int temp = end;
	vector<unsigned int> path;
	while (temp != start) {
		path.push_back(temp);
		temp = prevNode.at(temp);
	}
	path.push_back(temp);

	return make_tuple(path, pathLength.at(end), count);
}

//A* algorithm
//As the crow flies heuristic (distance formula) best for any-direction implementation
tuple<vector<unsigned int>, double, unsigned long> Graph::aPath(unsigned int start, unsigned int end) {
	// Decleare starting states
	vector<double> pathLength(graph3D.size(), INFINITY);
	vector<int> prevNode(graph3D.size(), start);
	priority_queue<pair<double, unsigned int>, vector<pair<double, unsigned int>>, greater<pair<double, unsigned int>>> leftover;
	unsigned long count = 0;

	// Set up initial values for the priority queue
	leftover.push(make_pair(0.0, start));
	for (auto it = graph3D.begin(); it != graph3D.end(); it++) {
		if (it->first != start) {
			leftover.push(make_pair(INFINITY, it->first));
		}
	}
	// Initial distance to first node will always be 0;
	pathLength.at(start) = 0.0;


	//end point distances
	double endX = identifiers.at(end).getX();
	double endY = identifiers.at(end).getY();
	double endZ = identifiers.at(end).getZ();
	// A* find good enough path
	while (!leftover.empty()) {
		unsigned int curr = leftover.top().second;
		leftover.pop();
		//cout << "curr: " << curr;

		if (curr == end) {
			//cout << "curr == end " << endl;
			break;
		}

		// Cycle through the connected edges
		for (auto it = graph3D.find(curr)->second.begin(); it != graph3D.find(curr)->second.end(); it++) {
			unsigned int vertex = it->first;
			double dist = it->second;
			double heuristicDistance = sqrt(pow(endX - identifiers.at(vertex).getX(), 2) + pow(endY - identifiers.at(vertex).getY(), 2) + pow(endZ - identifiers.at(vertex).getZ(), 2));
			count++;

			// Relaxation for all edges involved
			if (pathLength.at(vertex) > pathLength.at(curr) + dist) {
				pathLength.at(vertex) = pathLength.at(curr) + dist;
				leftover.push(make_pair(pathLength.at(vertex) + heuristicDistance, vertex));
				prevNode.at(vertex) = curr;
			}
		}
	}

	// Makes a vector of the path taken to get to selected node in reverse order (last->first node)
	unsigned int temp = end;
	vector<unsigned int> path;
	while (temp != start) {
		path.push_back(temp);
		temp = prevNode.at(temp);
	}
	path.push_back(temp);

	return make_tuple(path, pathLength.at(end), count);
}