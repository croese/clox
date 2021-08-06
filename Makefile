objects = main.o chunk.o memory.o

clox : $(objects)
	cc -o clox $(objects)

.PHONY: clean
clean:
	rm clox $(objects)