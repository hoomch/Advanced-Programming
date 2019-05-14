#ifndef __OPERAND_H__
#define __OPERAND_H__

#include "libraries.hpp"
#include "node.hpp"

using namespace std;
class Operand : public Node{
public:
	Operand(int index , int value);
	bool is_subjoin_possible();
protected:
	int value;
};

#endif