CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

sparseMatrixTest.out :sparseMatrixTest.o sparseMatrix.o
	$(CC) -o $@ $^

sparseMatrixTest.o : sparseMatrixTest.c sparseMatrix.h
	$(CC) -c -o $@ $<

sparseMatrix.o : sparseMatrix.c sparseMatrix.h
	$(CC) -c -o $@ $<

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)
