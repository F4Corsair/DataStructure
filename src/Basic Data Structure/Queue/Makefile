CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

intCircularQueueTest.out :intCircularQueueTest.o intCircularQueue.o
	$(CC) -o $@ $^

intCircularQueueTest.o : intCircularQueueTest.c
	$(CC) -c -o $@ $<

intCircularQueue.o : intCircularQueue.c intCircularQueue.h
	$(CC) -c -o $@ $<

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)
