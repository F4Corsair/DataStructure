CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

mazeDFSTest.out :mazeDFSTest.o mazeTraverseDFS.o
	$(CC) -o $@ $^

mazeDFSTest.o : mazeDFSTest.c mazeTraverseDFS.h
	$(CC) -c -o $@ $<

mazeTraverseDFS.o : mazeTraverseDFS.c mazeTraverseDFS.h
	$(CC) -c -o $@ $<

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)
