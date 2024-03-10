CFLAGS  = -g -Wall -pedantic
CC  = gcc

all: \
	chunk_methods \
	chunk \

chunk_methods: chunk_methods.h chunk_methods.o
	$(CC) -c $(CFLAGS) $@.c -o $@

chunk: chunk_methods.o chunk.o chunk_methods.h
	$(CC) $(CFLAGS) $@.c -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f chunk_methods
	rm -f chunk
	rm -f *.o
	rm -f *.out
	rm -f *.err
	rm -rf *.dSYM
