CC = gcc -g
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

testAVL.out :testAVL.o avlTree.o
	$(CC) -o $@ $^

testAVL.o : testAVL.c avlTree.h
	$(CC) -c -o $@ $<

avlTree.o : avlTree.c avlTree.h
	$(CC) -c -o $@ $<

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)
