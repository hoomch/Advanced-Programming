#include "operand.hpp"
Operand::Operand(int index , int value) : Node(index) {
	this->value = value;
}
bool Operand::is_subjoin_possible(){
	return 0;
}