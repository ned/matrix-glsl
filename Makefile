CC=gcc
CFLAGS=-Wall -Werror -lm

# delete .o files, project isn't big enough that I care
# about saving time and it adds clutter
.INTERMEDIATE: matrix.o

test: test.c matrix.o
	$(CC) $(CFLAGS) $^ -o $@
