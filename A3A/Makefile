# Compiler --branch
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Target names
LIBRARY_OBJECT = IndianRailways.o
TEST_PROGRAM = IndianRailwaysTest

# Source files
LIBRARY_SRC = IndianRailways.cpp
LIBRARY_HEADER = IndianRailways.h
TEST_SRC = main.cpp

# Default target to build the test program
all: $(TEST_PROGRAM)

# Build the library object
$(LIBRARY_OBJECT): $(LIBRARY_SRC) $(LIBRARY_HEADER)
	$(CXX) $(CXXFLAGS) -c $(LIBRARY_SRC) -o $(LIBRARY_OBJECT)

# Build the test program by linking the library object
$(TEST_PROGRAM): $(LIBRARY_OBJECT) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) $(LIBRARY_OBJECT) -o $(TEST_PROGRAM)

# Clean up all generated files
clean:
	rm -f $(LIBRARY_OBJECT) $(TEST_PROGRAM)

# Phony targets to ensure 'clean' always runs
.PHONY: all clean
