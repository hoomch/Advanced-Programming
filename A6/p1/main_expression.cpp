#include "tree.hpp"

int main() {
  Tree tree;
  try{
    /*tree.add_operator_node(0, NO_PARENT, Add);
    tree.add_operator_node(1, 0, Multiply);
    tree.add_number_node(2, 0, 5);
    tree.add_number_node(3, 1, 2);
    tree.add_number_node(4, 1, 3);*/
    tree.add_number_node(0 , NO_PARENT , 3);
    tree.add_number_node(3, 0 , 4);
  }catch(const char* error){cerr << error <<endl;}
  int result = tree.evaluate();
  //cout << result << endl; // output will be 11
}

/*
     +
    / \
   *   5
  / \
 2   3

*/
 