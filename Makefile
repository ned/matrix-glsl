CC=gcc

CFLAGS=-Wall -Wextra -Werror -std=c11
CFLAGS+=-Wfloat-equal
CFLAGS+=-Wshadow
CFlAGS+=-Wconversion
CFLAGS+=-O2
CFLAGS+=-Wsuggest-attribute=pure -Wsuggest-attribute=const

LDLIBS=-lm

# delete .o files, project isn't big enough that I care
# about saving time and it adds clutter
.INTERMEDIATE: matrix.o

test: test.c matrix.o
	$(CC) $(CFLAGS) -Wno-float-equal -Wno-suggest-attribute=pure $(LDLIBS) $^ -o $@
