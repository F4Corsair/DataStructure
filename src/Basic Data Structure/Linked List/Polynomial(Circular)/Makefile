CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

listPolyTest.out :listPolyTest.o circularListPolynomial.o
	$(CC) -o $@ $^

listPolyTest.o : listPolyTest.c circularListPolynomial.h
	$(CC) -c -o $@ $<

circularListPolynomial.o : circularListPolynomial.c circularListPolynomial.h
	$(CC) -c -o $@ $<

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)
