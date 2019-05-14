CPPFLAGS = -std=c++11 
main : Goods.o User.o Program.o main.o Factor.o Request.o
		g++ Goods.o User.o Program.o main.o Factor.o Request.o -o a.out

main.o : main.cpp Program.o 
		g++ $(CPPFLAGS) -c main.cpp
Program.o : Program.cpp Goods.o User.o Factor.o
		g++ $(CPPFLAGS) -c Program.cpp
User.o : User.cpp
		g++ $(CPPFLAGS) -c User.cpp
Goods.o : Goods.cpp
		g++ $(CPPFLAGS) -c Goods.cpp
Factor.o : Factor.cpp
		g++ $(CPPFLAGS) -c Factor.cpp
Request.o: Request.cpp Goods.o
		g++ $(CPPFLAGS) -c Request.cpp

clean:
	rm -f *.o *.out
