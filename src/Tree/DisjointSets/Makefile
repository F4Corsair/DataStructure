CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

equivalentClassBySets.out : equivalentClassBySets.o disjointSets.o
	$(CC) -o $@ $^

equivalentClassBySets.o : equivalentClassBySets.c
	$(CC) -o $@ $< -c

disjointSets.o : disjointSets.c disjointSets.h
	$(CC) -o $@ $< -c

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)