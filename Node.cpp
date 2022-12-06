#include "Node.h"

// Constructor for a node that takes in the coordinate values and makes an associated unique string
Node::Node(unsigned int x, unsigned int y, unsigned int z) {
	this->x = x;
	this->y = y;
	this->z = z;

	// This makes the string storing the coordinates unique and able to be compared
	ostringstream ss;
	ss << setw(width) << setfill('0') << x;
	ss << setw(width) << setfill('0') << y;
	ss << setw(width) << setfill('0') << z;
	uniqueID = ss.str();
	ss.clear();
}

// Copy constructor
Node::Node(const Node& n) {
	this->x = n.getX();
	this->y = n.getY();
	this->z = n.getZ();
	this->uniqueID = n.getID();
}

// Copy assignment operator
Node& Node::operator=(const Node& n) {
	this->x = n.getX();
	this->y = n.getY();
	this->z = n.getZ();
	this->uniqueID = n.getID();
	return *this;
}

// Returns a vector of the coordinates of a node
vector<unsigned int> Node::getXYZ() const {
	return vector<unsigned int>{x, y, z};
}

// Returns x
unsigned int Node::getX() const {
	return x;
}

// Returns y
unsigned int Node::getY() const {
	return y;
}

// Returns z
unsigned int Node::getZ() const {
	return z;
}

// Returns the unique ID
string Node::getID() const {
	return uniqueID;
}

// Comparison operator for the map
bool Node::operator<(const Node& other) const {
	return (this->uniqueID < other.getID());
}

// Comparison function for uniqueness
bool Node::operator==(const Node& other) const {
	return (this->x == other.getX() && this->y == other.getY() && this->z == other.getZ());
}