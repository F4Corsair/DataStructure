CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

polynomialIntTest.out :polynomialIntTest.o polynomial_int.o
	$(CC) -o $@ $^

polynomialIntTest.o : polynomialIntTest.c polynomial_int.h
	$(CC) -c -o $@ $<

polynomial_int.o : polynomial_int.c polynomial_int.h
	$(CC) -c -o $@ $<

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)
