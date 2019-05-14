CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
JEEKJEEK_DIR=JeekJeek

all: $(BUILD_DIR) server.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/server_main.o: server/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/main.cpp -o $(BUILD_DIR)/server_main.o

server.out: $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/server_main.o $(BUILD_DIR)/jeekJeek.o $(BUILD_DIR)/user.o $(BUILD_DIR)/jeek.o $(BUILD_DIR)/hashtag.o $(BUILD_DIR)/message.o $(BUILD_DIR)/idMaker.o $(BUILD_DIR)/webInterface.o
	$(CC) $(CF) $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/server_main.o $(BUILD_DIR)/jeekJeek.o $(BUILD_DIR)/user.o $(BUILD_DIR)/jeek.o $(BUILD_DIR)/hashtag.o $(BUILD_DIR)/message.o $(BUILD_DIR)/idMaker.o -o server.out $(BUILD_DIR)/webInterface.o

$(BUILD_DIR)/webInterface.o: server/webInterface.cpp server/webInterface.hpp
	$(CC) -c server/webInterface.cpp -o $(BUILD_DIR)/webInterface.o

$(BUILD_DIR)/jeekJeek.o: $(JEEKJEEK_DIR)/jeekJeek.cpp $(JEEKJEEK_DIR)/jeekJeek.hpp
	$(CC) -c $(JEEKJEEK_DIR)/jeekJeek.cpp -o $(BUILD_DIR)/jeekJeek.o

$(BUILD_DIR)/user.o: $(JEEKJEEK_DIR)/user.cpp $(JEEKJEEK_DIR)/user.hpp
	$(CC) -c $(JEEKJEEK_DIR)/user.cpp -o $(BUILD_DIR)/user.o

$(BUILD_DIR)/jeek.o: $(JEEKJEEK_DIR)/jeek.cpp $(JEEKJEEK_DIR)/jeek.hpp
	$(CC) -c $(JEEKJEEK_DIR)/jeek.cpp -o $(BUILD_DIR)/jeek.o

$(BUILD_DIR)/hashtag.o: $(JEEKJEEK_DIR)/hashtag.cpp $(JEEKJEEK_DIR)/hashtag.hpp
	$(CC) -c $(JEEKJEEK_DIR)/hashtag.cpp -o $(BUILD_DIR)/hashtag.o

$(BUILD_DIR)/message.o: $(JEEKJEEK_DIR)/message.cpp $(JEEKJEEK_DIR)/message.hpp
	$(CC) -c $(JEEKJEEK_DIR)/message.cpp -o $(BUILD_DIR)/message.o

$(BUILD_DIR)/idMaker.o: $(JEEKJEEK_DIR)/idMaker.cpp $(JEEKJEEK_DIR)/idMaker.hpp
	$(CC) -c $(JEEKJEEK_DIR)/idMaker.cpp -o $(BUILD_DIR)/idMaker.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out &> /dev/null
