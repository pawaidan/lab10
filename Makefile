CC=gcc
CFLAGS=-lWarn -pedantic

tempread.o: tempread.c tempread.h
	cc -c tempread.c -o tempread.o

tempread: tempread.o
	cc tempread.o -o tempread

all:	tempread

clean:
	rm tempread.o