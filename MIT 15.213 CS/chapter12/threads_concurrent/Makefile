CC = gcc
CFLAGS = -O2 -Wall -I .

# This flag includes the Pthreads library on a Linux box.
# Others systems will probably require something different.
LIB = -lpthread

all: threads_echoser badcnt corcnt

threads_echoser: threads_echoser.c csapp.o
	$(CC) $(CFLAGS) -o threads_echoser threads_echoser.c csapp.o $(LIB)

badcnt: badcnt.c csapp.o
	$(CC) $(CFLAGS) -o badcnt badcnt.c csapp.o $(LIB)

corcnt: corcnt.c csapp.o
	$(CC) $(CFLAGS) -o corcnt corcnt.c csapp.o $(LIB)

csapp.o: csapp.c
	$(CC) $(CFLAGS) -c csapp.c

clean:
	rm -f *.o iterative_io_mul badcnt corcnt concurrent_io_mul *~