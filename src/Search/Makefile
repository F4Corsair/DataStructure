CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

all : linearSearchUniversal.out linearSearchSentinel.out binSearchUniversal.out bsearch.out binSearch.out

linearSearchUniversal.out : linearSearchUniversal.c
	$(CC) -o $@ $^

linearSearchSentinel.out : linearSearchSentinel.c
	$(CC) -o $@ $^

binSearchUniversal.out : binSearchUniversal.c
	$(CC) -o $@ $^

bsearch.out : bsearch.c
	$(CC) -o $@ $^

binSearch.out : binSearch.c
	$(CC) -o $@ $^

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)