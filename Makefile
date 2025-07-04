CC = gcc
MEM_IMPL=./oneshot/oneshot.c
SRC = main.c $(MEM_IMPL) 
TARGET = main

all:
	$(CC) $(SRC) $(INCLUDE) -o $(TARGET) 

clean:
	rm $(TARGET)
