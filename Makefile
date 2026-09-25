CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Isrc
SRC = src/shell.c src/parse.c src/builtin.c src/execute.c
TARGET = myshell

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean