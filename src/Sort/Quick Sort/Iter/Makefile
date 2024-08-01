CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

quickSortIter.out : quickSortIter.o linkedStack.o
	$(CC) -o $@ $^

quickSortIter.o : quickSortIter.c linkedStack.h
	$(CC) -c -o $@ $<

linkedStack.o : linkedStack.c linkedStack.h
	$(CC) -c -o $@ $<

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)