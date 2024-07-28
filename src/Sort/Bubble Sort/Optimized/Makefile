CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

optiBubbleSort.out : optiBubbleSort.c
	$(CC) -o $@ $^

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)