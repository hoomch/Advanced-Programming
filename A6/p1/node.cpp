#include "node.hpp"
Node::Node(int index){
	this->index = index;
}
void Node::add_node(Node* newNode){
	cout << this->is_subjoin_possible()<< endl;
	if (this->is_subjoin_possible())
		nodes.push_back(newNode);
	else throw "subJoin is Not Possible !";
}
void Node::setIndex(int index){
	this-> index = index;
}
int Node::getIndex(){
	return index;
}
int Node::evaluateNode(){
	
}
vector <Node*> & Node::getNodes(){
	return nodes;
}
