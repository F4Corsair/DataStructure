CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

linkedListTest.out :linkedListTest.o linkedList.o
	$(CC) -o $@ $^

linkedListTest.o : linkedListTest.c linkedList.h
	$(CC) -c -o $@ $<

linkedList.o : linkedList.c linkedList.h
	$(CC) -c -o $@ $<

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)
