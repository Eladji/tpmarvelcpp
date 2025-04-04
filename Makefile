# Makefile for Marvel Superhero Game

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I.

# Target executable
TARGET = marvelgame

# Find all source files directly without specifying directories
SRCS := $(shell find . -name "*.cpp")

# Object files
OBJS := $(SRCS:.cpp=.o)

# Main target
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compiling source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(TARGET) $(OBJS)
	@echo "Cleaned up build files"

# Run target
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run
