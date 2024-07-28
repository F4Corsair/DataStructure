CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

heapSort.out : heapSort.c
	$(CC) -o $@ $^

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)