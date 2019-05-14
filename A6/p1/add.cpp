#include "add.hpp"
ADD::ADD(int index) : Node(index) {

}
bool ADD::is_subjoin_possible(){
	if (nodes.size() < 2) return 1;
	else return 0;
}