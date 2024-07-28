CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

countingSort.out : countingSort.c
	$(CC) -o $@ $^

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)