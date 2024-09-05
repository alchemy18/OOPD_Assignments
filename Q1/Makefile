# Define compiler and flags
CXX = g++
CXXFLAGS_DEBUG = -g -Wall -std=c++17
CXXFLAGS_OPTIMIZED = -O2 -Wall -std=c++17

# Define target executable names
TARGET_DEBUG = question1_debug
TARGET_OPTIMIZED = question1_optimized

# Define the source file
SRC = question1.cpp

# Define the object files
OBJ = $(SRC:.cpp=.o)

# Default target: build both versions
all: $(TARGET_DEBUG) $(TARGET_OPTIMIZED)

# Rule to build the debugging version
$(TARGET_DEBUG): $(OBJ)
	$(CXX) $(CXXFLAGS_DEBUG) -o $@ $(OBJ)

# Rule to build the optimized version
$(TARGET_OPTIMIZED): $(OBJ)
	$(CXX) $(CXXFLAGS_OPTIMIZED) -o $@ $(OBJ)

# Rule to compile the source file into object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS_DEBUG) -c $< -o $@

# Clean rule to remove all generated files
clean:
	rm -f $(TARGET_DEBUG) $(TARGET_OPTIMIZED) $(OBJ)

# Rule to remove all generated files and reset build
distclean: clean
	rm -f $(TARGET_DEBUG) $(TARGET_OPTIMIZED)
