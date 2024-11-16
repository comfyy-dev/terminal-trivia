# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Source files
SRCS = source.c trivia.c question.c

# Output binaries
RELEASE_BIN = comfytrivia
DEBUG_BIN = comfytrivia_debug

# Release build and run
release: CFLAGS += -O2
release:
	$(CC) $(CFLAGS) -o $(RELEASE_BIN) $(SRCS)
	./$(RELEASE_BIN) q_a.txt

# Debug build and run
debug: CFLAGS += -DDEBUG -g
debug:
	$(CC) $(CFLAGS) -o $(DEBUG_BIN) $(SRCS)
	./$(DEBUG_BIN) test.csv

# Clean up generated files
clean:
	rm -f $(RELEASE_BIN) $(DEBUG_BIN)