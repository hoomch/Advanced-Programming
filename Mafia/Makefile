CPPFLAGS = -std=c++11 
main : Person.o Room.o Program.o main.o Bigman.o Detective.o Doctor.o Joker.o Silencer.o Vote.o
		g++ Person.o Room.o Program.o main.o Bigman.o Detective.o Doctor.o Joker.o Silencer.o Vote.o -o a.out

main.o : main.cpp Program.o 
		g++ $(CPPFLAGS) -c main.cpp
Program.o : Program.cpp Person.o Room.o Bigman.o Detective.o Doctor.o Joker.o Silencer.o
		g++ $(CPPFLAGS) -c Program.cpp
Person.o : Person.cpp
		g++ $(CPPFLAGS) -c Person.cpp
Room.o : Room.cpp Person.o Room.o Bigman.o Detective.o Doctor.o Joker.o Silencer.o Vote.o
		g++ $(CPPFLAGS) -c Room.cpp
Bigman.o : Bigman.cpp Person.o
		g++ $(CPPFLAGS) -c Bigman.cpp
Detective.o: Detective.cpp Person.o
		g++ $(CPPFLAGS) -c Detective.cpp
Doctor.o: Doctor.cpp Person.o
		g++ $(CPPFLAGS) -c Doctor.cpp
Joker.o: Joker.cpp Person.o
		g++ $(CPPFLAGS) -c Joker.cpp
Silencer.o: Silencer.cpp Person.o
		g++ $(CPPFLAGS) -c Silencer.cpp
Vote.o: Vote.cpp 
		g++ $(CPPFLAGS) -c Vote.cpp

clean:
	rm -f *.o *.out