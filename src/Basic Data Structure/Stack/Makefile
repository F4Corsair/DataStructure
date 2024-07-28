CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

intStackTest.out :intStackTest.o intStack.o
	$(CC) -o $@ $^

intStackTest.o : intStackTest.c
	$(CC) -c -o $@ $<

intStack.o : intStack.c intStack.h
	$(CC) -c -o $@ $<

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)
