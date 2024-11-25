# Compiler and flags
CXX = g++
CXXFLAGS = 
LDFLAGS = -l sqlite3

# Target executable
TARGET = program2_out
SRC = program2.cpp

# Build the program
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f $(TARGET)
