# Makefile for EECS 348 Lab 9
# Name: Andrew Aubuchon
# Date: October 27, 2025
# KUID: 3165875

CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Executable name
TARGET = matrix_lab

# Default rule
all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up build files
clean:
	rm -f $(TARGET)
