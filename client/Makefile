CC := clang++
CFLAGS += -std=c++17 -Wall -Wextra -pedantic -I./src/ -I../common/ -g -O0
LDFLAGS += -lWs2_32

OUT := ../chatapp.exe
SRC := Client.cpp ../common/Message.cpp
OBJ := ./obj/Client.o ./obj/WS2.o ./obj/Message.o

$(OUT): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $(OUT)

./obj/WS2.o: ../common/WS2.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

./obj/Message.o: ../common/Message.cpp
	$(CC) $(CFLAGS) -c $^ -o $@


./obj/%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
