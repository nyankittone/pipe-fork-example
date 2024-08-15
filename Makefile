CC := cc
CFLAGS := -std=c99 -pedantic-errors -Wall
BIN := bruh

.PHONY: all $(BIN) clean

all: $(BIN)

$(BIN): main.c
	$(CC) $(CFLAGS) main.c -o $(BIN)

clean:
	rm $(BIN); true

