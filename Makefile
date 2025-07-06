CC = gcc
CFLAGS = -Wall -Wextra
SRC = main.c 

.PHONY: clean oneshot bump block

oneshot.out: oneshot/oneshot.c
	$(CC) ${CFLAGS} oneshot/$(SRC) $< -o $@
oneshot: oneshot.out

bump.out: bump/bump.c
	$(CC) ${CFLAGS} bump/$(SRC) $< -o $@ 
bump: bump.out

block.out: block/block.c
	$(CC) ${CFLAGS} block/$(SRC) $< -o $@ 
block: block.out

clean:
	rm -f oneshot.out bump.out block.out

