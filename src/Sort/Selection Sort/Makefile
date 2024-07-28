CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

selectionSort.out : selectionSort.c
	$(CC) -o $@ $^

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)