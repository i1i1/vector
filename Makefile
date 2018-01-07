CC=gcc
CFLAGS=-Wall
RM=rm -rf
OUT=vector

all: build

build: 
	$(CC) $(CFLAGS) -o $(OUT) main.c

debug: CFLAGS+=-DDEBUG_ON
debug: build

clean:
	$(RM) *.o $(OUT)

