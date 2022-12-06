#include "Hasher.h"

	
size_t Hasher::operator()(const Node& n) const {
	using std::size_t;
	using std::hash;
	using std::string;
	return (hash<string>()(n.getID()));
}