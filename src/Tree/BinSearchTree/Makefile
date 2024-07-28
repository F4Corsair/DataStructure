CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

BSTtest.out : BSTtest.o binSearchTree.o
	$(CC) -o $@ $^

BSTtest.o : BSTtest.c
	$(CC) -o $@ $< -c

binSearchTree.o : binSearchTree.c binSearchTree.h
	$(CC) -o $@ $< -c

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)