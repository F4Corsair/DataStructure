CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTS = $(wildcard *.out)

degreeCheckTest.out :degreeCheckTest.o degreeCheck.o
	$(CC) -o $@ $^

degreeCheckTest.o : degreeCheckTest.c degreeCheck.h
	$(CC) -c -o $@ $<

degreeCheck.o : degreeCheck.c degreeCheck.h
	$(CC) -c -o $@ $<

.PHONY : clean

clean:
	rm -f $(OBJS) $(OUTS)
