#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;
class Node
{
	public:
		// Constructor for a node that takes in the coordinate values and makes an associated unique string
		Node(unsigned int x, unsigned int y, unsigned int z);
		Node(const Node& n);
		Node& operator=(const Node& n);

		// Getters for all of the coordinate data
		vector<unsigned int> getXYZ() const;
		unsigned int getX() const;
		unsigned int getY() const;
		unsigned int getZ() const;
		string getID() const;

		// Used for the sorting in the map
		bool operator<(const Node& other) const;
		bool operator==(const Node& other) const;

	private:
		// Node variables
		const unsigned short width = 4; //TODO: change later when input range is finalized
		unsigned int x, y, z;
		string uniqueID;
};

