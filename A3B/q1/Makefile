# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -I/Users/pragya/Document/include
LDFLAGS = -L/Users/pragya/Document/lib -lboost_system

# Target executable
TARGET = program1
SRC = program1.cpp

# Build the program
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(SRC)

# Run the program
run: $(TARGET)
	export DYLD_LIBRARY_PATH=/Users/pragya/Document/lib:$$DYLD_LIBRARY_PATH && ./$(TARGET)

# Clean up
clean:
	rm -f $(TARGET)
