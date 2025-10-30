

CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Output executable name
TARGET = lab9

# Source file
SRC = Source1.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
