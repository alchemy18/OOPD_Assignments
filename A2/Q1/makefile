# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11

# Source files
SRC = main.cpp

# Binaries
DEBUG_BIN = debug_output
RELEASE_BIN = optimised_output

# Build directory
BUILD_DIR = build

# Flags for debug and release builds
DEBUG_FLAGS = -g -O0 -Wall -Wextra
RELEASE_FLAGS = -O3 -Wall

# Default target
all: $(BUILD_DIR)/$(DEBUG_BIN) $(BUILD_DIR)/$(RELEASE_BIN)

# Build debug version
$(BUILD_DIR)/$(DEBUG_BIN): $(SRC)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -o $(BUILD_DIR)/$(DEBUG_BIN) $(SRC)
	@echo "Debug binary built: $(BUILD_DIR)/$(DEBUG_BIN)"

# Build release (optimized) version
$(BUILD_DIR)/$(RELEASE_BIN): $(SRC)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(RELEASE_FLAGS) -o $(BUILD_DIR)/$(RELEASE_BIN) $(SRC)
	@echo "Release binary built: $(BUILD_DIR)/$(RELEASE_BIN)"

# Clean the build directory
clean:
	@rm -rf $(BUILD_DIR)
	@echo "Build directory cleaned."

# Phony targets
.PHONY: all clean
