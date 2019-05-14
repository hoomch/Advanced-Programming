#include "multiply.hpp"
MULTIPLY::MULTIPLY(int index) : Node(index) {

}
bool MULTIPLY::is_subjoin_possible(){
	if (nodes.size() < 2) return 1;
	else return 0;
}