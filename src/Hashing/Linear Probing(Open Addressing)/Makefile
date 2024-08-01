CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

linearProbingHashTest.out :linearProbingHashTest.o linearProbingHash.o
	$(CC) -o $@ $^

linearProbingHashTest.o : linearProbingHashTest.c linearProbingHash.h
	$(CC) -c -o $@ $<

linearProbingHash.o : linearProbingHash.c linearProbingHash.h
	$(CC) -c -o $@ $<

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)
