CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

heapTest.out : heapTest.o heap.o
	$(CC) -o $@ $^

heapTest.o : heapTest.c heap.h
	$(CC) -o $@ $< -c

heap.o : heap.c heap.h
	$(CC) -o $@ $< -c

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)