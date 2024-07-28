CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

classHeightSort.out : classHeightSort.o tournamentTree.o
	$(CC) -o $@ $^

classHeightSort.o : classHeightSort.c
	$(CC) -o $@ $< -c

tournamentTree.o : tournamentTree.c tournamentTree.h
	$(CC) -o $@ $< -c

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)