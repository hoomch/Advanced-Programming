a.out: main_expression.o node.o operand.o not.o med.o add.o multiply.o tree.o
	g++ main_expression.o node.o operand.o not.o med.o add.o multiply.o tree.o -o a.out
main_expression.o: main_expression.cpp
	g++ -c main_expression.cpp -o main_expression.o
node.o: node.cpp
	g++ -c node.cpp -o node.o
operand.o: operand.cpp
	g++ -c operand.cpp -o operand.o
not.o: not.cpp
	g++ -c not.cpp -o not.o
med.o: med.cpp
	g++ -c med.cpp -o med.o
add.o: add.cpp
	g++ -c add.cpp -o add.o
multiply.o: multiply.cpp
	g++ -c multiply.cpp -o multiply.o
tree: tree.cpp
	g++ -c tree.cpp -o tree.o
clean:
	rm -r *.o 