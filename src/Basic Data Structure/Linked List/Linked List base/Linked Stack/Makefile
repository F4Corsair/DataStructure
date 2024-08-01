CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

linkedStack.out :linkedStack.o ../linkedList.o
	$(CC) -o $@ $^

linkedStack.o : linkedStack.c ../linkedList.h
	$(CC) -c -o $@ $<

../linkedList.o : ../linkedList.c ../linkedList.h
	$(CC) -c -o $@ $<

.PHONY : clean cleanAll

clean:
	rm -f $(OBJS) $(OUTS)

cleanAll :
	rm -f $(OBJS) $(OUTS) ../linkedList.o