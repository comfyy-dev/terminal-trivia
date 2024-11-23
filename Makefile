# Compiler and flags
CC = gcc
CFLAGS = -D_POSIX_C_SOURCE=199309L -Wall -Wextra -std=c99

# Source files
SRCS = source.c trivia.c question.c

# Output binaries
RELEASE_BIN = comfytrivia
DEBUG_BIN = comfytrivia_debug

# Release build and run
release: CFLAGS += -DRELEASE -O2
release:
	$(CC) $(CFLAGS) -o $(RELEASE_BIN) $(SRCS)
	./$(RELEASE_BIN) example.txt

# Debug build and run
debug: CFLAGS += -DDEBUG -g
debug:
	$(CC) $(CFLAGS) -o $(DEBUG_BIN) $(SRCS)
	./$(DEBUG_BIN) example.txt

# Clean up generated files
clean:
	rm -f $(RELEASE_BIN) $(DEBUG_BIN)