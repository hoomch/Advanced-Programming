#ifndef __MULTIPLY_H__
#define __MULTIPLY_H__

#include "libraries.hpp"
#include "node.hpp"

using namespace std;
class MULTIPLY : public Node{
public:
	MULTIPLY(int index);
	bool is_subjoin_possible();
};

#endif