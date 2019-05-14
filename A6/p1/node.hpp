#ifndef __NODE_H__
#define __NODE_H__

#include "libraries.hpp"

using namespace std;
class Node{
public:
	Node(int index);
	void add_node(Node* newNode);
	virtual bool is_subjoin_possible() = 0;
	void setIndex(int index);
	int getIndex();
	int evaluateNode();
	vector <Node*> & getNodes();
protected:
	int index;
	vector <Node*> nodes;
};

#endif