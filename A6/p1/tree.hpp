#ifndef __TREE_H__
#define __TREE_H__

#include "libraries.hpp"
#include "node.hpp"
#include "multiply.hpp"
#include "add.hpp"
#include "med.hpp"
#include "not.hpp"
#include "operand.hpp"

#define NO_PARENT -1
using namespace std;
enum OperatorType { Add, Multiply, Not, Median};

class Tree{
public:
	Tree();
	void add_number_node(int index, int parent_index, int value);
	void add_operator_node(int index, int parent_index, OperatorType type);
	int evaluate();
private:
	Node *root;
};

#endif
