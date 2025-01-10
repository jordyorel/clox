CC=gcc
CFLAGS=-I./src -Wall
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)
TARGET=clox

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)