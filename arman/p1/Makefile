all: interface.o jeekJeek.o user.o jeek.o hashtag.o message.o comment.o reply.o idMaker.o main.o
	g++ interface.o jeekJeek.o user.o jeek.o hashtag.o message.o comment.o reply.o idMaker.o main.o

main.o: main.cpp
	g++ -c main.cpp
interface.o: interface.cpp interface.hpp
	g++ -c interface.cpp
jeekJeek.o: jeekJeek.cpp jeekJeek.hpp
	g++ -c jeekJeek.cpp
user.o: user.cpp user.hpp
	g++ -c user.cpp
jeek.o: jeek.cpp jeek.hpp
	g++ -c jeek.cpp
hashtag.o: hashtag.cpp hashtag.hpp
	g++ -c hashtag.cpp
message.o: message.cpp
	g++ -c message.cpp	
comment.o: comment.cpp
	g++ -c comment.cpp
reply.o: reply.cpp
	g++ -c reply.cpp
idMaker.o: idMaker.cpp
	g++ -c idMaker.cpp
clean:
	rm -rf *.o
