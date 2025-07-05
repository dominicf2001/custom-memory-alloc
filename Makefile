CC = gcc
CFLAGS = -Wall -Wextra
SRC = main.c 

.PHONY: clean oneshot bump

oneshot.out: oneshot/oneshot.c
	$(CC) ${CFLAGS} $(SRC) $< -o $@
oneshot: oneshot.out

bump.out: bump/bump.c
	$(CC) ${CFLAGS} $(SRC) $< -o $@ 
bump: bump.out

clean:
	rm -f oneshot.out bump.out

