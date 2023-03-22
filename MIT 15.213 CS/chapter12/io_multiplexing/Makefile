CC = gcc
CFLAGS = -O2 -Wall -I .

# This flag includes the Pthreads library on a Linux box.
# Others systems will probably require something different.
LIB = -lpthread

all: iterative_io_mul concurrent_io_mul

iterative_io_mul: iterative_io_mul.c csapp.o
	$(CC) $(CFLAGS) -o iterative_io_mul iterative_io_mul.c csapp.o $(LIB)

concurrent_io_mul: concurrent_io_mul.c csapp.o
	$(CC) $(CFLAGS) -o concurrent_io_mul concurrent_io_mul.c csapp.o $(LIB)

csapp.o: csapp.c
	$(CC) $(CFLAGS) -c csapp.c

clean:
	rm -f *.o iterative_io_mul concurrent_io_mul *~