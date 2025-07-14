CC = gcc
CFLAGS = -g -Wall -Wextra -std=c23 -pedantic
objects = main.o chunk.o memory.o debug.o value.o lines.o

clox: $(objects)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm $(objects) clox
