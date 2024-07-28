CC = gcc -g
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

linkedQueue.out :linkedQueue.o ../linkedList.o
	$(CC) -o $@ $^

linkedQueue.o : linkedQueue.c
	$(CC) -c -o $@ $<

../linkedList.o : ../linkedList.c ../linkedList.h
	$(CC) -c -o $@ $<

.PHONY : clean cleanAll

clean:
	rm -f $(OBJS) $(OUTS)

cleanAll :
	rm -f $(OBJS) $(OUTS) ../linkedList.o
