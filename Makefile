CC=gcc
CFLAGS=-Wall -Wextra -g
OUT=vector

$(OUT): main.c
	$(CC) $(CFLAGS) -o $(OUT) $<

clean:
	$(RM) *.o $(OUT)

