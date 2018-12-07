CC=gcc
CFLAGS=-Wall -g
RM=rm -rf
OUT=vector

all: build

build: pre
	$(CC) $(CFLAGS) -o $(OUT) main.o vector.o

pre:
	$(CC) $(CFLAGS) -c main.c vector.c

debug: CFLAGS+=-DDEBUG_ON
debug: build

clean:
	$(RM) *.o $(OUT)

