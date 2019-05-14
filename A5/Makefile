UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
		HEAD := \"sdlheaders/mac.hpp\"
  	CCFLAGS= -framework SDL2 -framework SDL2_image -framework SDL2_ttf
else
		HEAD := \"sdlheaders/linux.hpp\"
		CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf
endif
run: main.o swipeBrickBreaker.o user.o ball.o table.o myString.o block.o globalFunctions.o rsdl.o
	g++ objects/main.o src/rsdl.o objects/swipeBrickBreaker.o objects/user.o objects/ball.o objects/table.o objects/myString.o objects/block.o objects/globalFunctions.o $(CCFLAGS) -o run
main.o: main.cpp
	g++ -c main.cpp -o objects/main.o
swipeBrickBreaker.o: swipeBrickBreaker.cpp
	g++ -c swipeBrickBreaker.cpp -o objects/swipeBrickBreaker.o
user.o: user.cpp
	g++ -c user.cpp -o objects/user.o
ball.o: ball.cpp
	g++ -c ball.cpp -o objects/ball.o
table.o: table.cpp
	g++ -c table.cpp -o objects/table.o
myString.o: myString.cpp
	g++ -c myString.cpp -o objects/myString.o
block.o:
	g++ -c block.cpp -o objects/block.o
globalFunctions.o: globalFunctions.cpp
	g++ -c globalFunctions.cpp -o objects/globalFunctions.o
rsdl.o: src/rsdl.hpp src/rsdl.cpp
	g++ -c src/rsdl.cpp -o src/rsdl.o
clean:
	rm -r *.o  