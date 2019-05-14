#include "not.hpp"
NOT::NOT(int index) : Node(index) {

}
bool NOT::is_subjoin_possible(){
	if (nodes.size() == 0) return 1;
	else return 0;
}