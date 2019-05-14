#ifndef __ADD_H__
#define __ADD_H__

#include "libraries.hpp"
#include "node.hpp"

using namespace std;
class ADD : public Node{
public:
	ADD(int index);
	bool is_subjoin_possible();

};

#endif