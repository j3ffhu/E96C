#
# Makefile that builds btest and other helper programs for Assignment No. 1
# 
CC = gcc
CFLAGS = -O -Wall -fwrapv
LIBS = -lm

all: btest

btest: btest.c bits.c decl.c tests.c btest.h bits.h
	$(CC) $(CFLAGS) $(LIBS) -o btest bits.c btest.c decl.c tests.c

# Forces a recompile. Used by the driver program. 
btestexplicit:
	$(CC) $(CFLAGS) $(LIBS) -o btest bits.c btest.c decl.c tests.c 

clean:
	rm -f *.o btest *~


