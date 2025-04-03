# Makefile for Marvel Superhero Game

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I.

# Target executable
TARGET = marvelgame

# Source directories
SRC_DIRS = . class class/Artefacts class/Artefacts/CursedStone class/Artefacts/HealthPotion \
           class/Artefacts/PowerAmulet class/SuperHero class/SuperHero/Hulk class/SuperHero/IronMan \
           class/SuperHero/Spider class/SuperHero/Docteur\ Strange class/Game class/Game/Player

# Find all source files
SRCS = main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

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
