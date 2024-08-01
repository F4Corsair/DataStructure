CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

quickSortOptiIter.out : quickSortOptiIter.o ../../Iter/linkedStack.o
	$(CC) -o $@ $^

quickSortOptiIter.o : quickSortOptiIter.c ../../Iter/linkedStack.h
	$(CC) -c -o $@ $<

../../Iter/linkedStack.o : ../../Iter/linkedStack.c ../../Iter/linkedStack.h
	$(CC) -c -o $@ $<

.PHONY : clean cleanAll

clean:
	rm -f $(OBJS) $(OUTS)

cleanAll:
	rm -f ../../Iter/linkedStack.o $(OBJS) $(OUTS)