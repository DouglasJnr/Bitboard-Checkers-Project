# Makefile for BitBoard Checkers

CC = gcc
CFLAGS = -Wall -g
TARGET = checkers
OBJS = bitops.o board.o game.o main.o

# Default target - build the game
all: $(TARGET)

# Link all object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "Build successful! Run with: ./$(TARGET)"

# Compile bitops.c
bitops.o: bitops.c bitops.h
	$(CC) $(CFLAGS) -c bitops.c

# Compile board.c
board.o: board.c board.h bitops.h
	$(CC) $(CFLAGS) -c board.c

# Compile game.c
game.o: game.c game.h board.h bitops.h
	$(CC) $(CFLAGS) -c game.c

# Compile main.c
main.o: main.c bitops.h board.h game.h
	$(CC) $(CFLAGS) -c main.c

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "Clean complete!"

# Run the game
run: $(TARGET)
	./$(TARGET)

# Help message
help:
	@echo "BitBoard Checkers Makefile"
	@echo "=========================="
	@echo "Available targets:"
	@echo "  make         - Build the game"
	@echo "  make all     - Build the game"
	@echo "  make clean   - Remove compiled files"
	@echo "  make run     - Build and run the game"
	@echo "  make help    - Show this help message"
