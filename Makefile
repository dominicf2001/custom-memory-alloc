CC = gcc
SRC = main.c ./oneshot/oneshot.c
INCLUDE = -I./oneshot
TARGET = main

all:
	$(CC) $(SRC) $(INCLUDE) -o $(TARGET) 

clean:
	rm $(TARGET)
