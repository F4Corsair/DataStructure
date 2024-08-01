CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

threadedBSTtest.out : threadedBSTtest.o threadedBST.o
	$(CC) -o $@ $^

threadedBSTtest.o : threadedBSTtest.c threadedBST.h
	$(CC) -o $@ $< -c

threadedBST.o : threadedBST.c threadedBST.h
	$(CC) -o $@ $< -c

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)