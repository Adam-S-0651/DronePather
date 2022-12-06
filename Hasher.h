#pragma once
#include "Node.h"
using namespace std;

// This class allows hashing of Node objects in an unordered map or set
class Hasher
{
	public:
		size_t operator()(const Node& n) const;
			
};
