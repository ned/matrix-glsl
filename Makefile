CFLAGS=-Wall -Wextra -Werror -std=c11
CFLAGS+=-Wfloat-equal
CFLAGS+=-Wshadow
CFlAGS+=-Wconversion
CFLAGS+=-O2

LDLIBS=-lm

test: test.o matrix.o
	$(CC) -o $@ $^ $(LDLIBS)

test.o: test.c
	$(CC) $(CFLAGS) -Wno-float-equal $^ -c
