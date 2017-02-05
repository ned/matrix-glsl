CC=gcc

CFLAGS=-Wall -Wextra -Werror
CFLAGS+=-Wfloat-equal
CFLAGS+=-Wshadow
CFlAGS+=-Wconversion
CFLAGS+=-O2

LDLIBS=-lm

# delete .o files, project isn't big enough that I care
# about saving time and it adds clutter
.INTERMEDIATE: matrix.o

test: test.c matrix.o
	$(CC) $(CFLAGS) -Wno-float-equal $(LDLIBS) $^ -o $@
