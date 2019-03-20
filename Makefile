CC = gcc

CFILES = $(shell find src/ -name "*.c")
OBJECTS = $(CFILES:.c=.o)
CFLAGS = -ggdb -Wall

ash: $(OBJECTS)
	$(CC) -o ash $(OBJECTS)

.PHONY: clean
clean:
	-rm ash $(OBJECTS) $(CFLAGS)


