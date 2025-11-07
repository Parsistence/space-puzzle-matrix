# Simple Makefile for Terminal Game

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
LDFLAGS = -lncurses
CPPFLAGS += -I../include

# Source files
SOURCES = main.cpp GameLogic.cpp TerminalImplementation.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
TARGET = terminal_game

# Default target
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Rule to compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean