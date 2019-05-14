#ifndef __MED_H__
#define __MED_H__

#include "libraries.hpp"
#include "node.hpp"

using namespace std;
class Med : public Node{
public:
	Med (int index);
	bool is_subjoin_possible();

};

#endif