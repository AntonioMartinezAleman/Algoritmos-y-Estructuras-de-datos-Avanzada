CXX = g++
CXXFLAGS = -Wall -std=c++17
SRC = main.cc nif.cc 
HEADERS = staticsequence.h sequence.h sortingmethods.h nif.h
TARGET = ordenacion

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
