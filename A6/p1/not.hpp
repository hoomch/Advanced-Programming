#ifndef __NOT_H__
#define __NOT_H__

#include "libraries.hpp"
#include "node.hpp"

using namespace std;
class NOT : public Node{
public:
	NOT(int index);
	bool is_subjoin_possible();
};

#endif