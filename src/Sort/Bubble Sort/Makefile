CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

bubbleSort.out : bubbleSort.c
	$(CC) -o $@ $^

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)