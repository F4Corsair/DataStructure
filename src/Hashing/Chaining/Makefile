CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

chainingHashTest.out :chainingHashTest.o chainingHash.o
	$(CC) -o $@ $^

chainingHashTest.o : chainingHashTest.c
	$(CC) -c -o $@ $<

chainingHash.o : chainingHash.c chainingHash.h
	$(CC) -c -o $@ $<

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)
