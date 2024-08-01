CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

mazeBFSTest.out :mazeBFSTest.o mazeTraverseBFS.o
	$(CC) -o $@ $^

mazeBFSTest.o : mazeBFSTest.c mazeTraverseBFS.h
	$(CC) -c -o $@ $<

mazeTraverseBFS.o : mazeTraverseBFS.c mazeTraverseBFS.h
	$(CC) -c -o $@ $<

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)
