# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Source files
SRCS = main.cpp \
	   classFunctions.cpp \
       functions.cpp \
       Library.cpp \
       LibraryItem.cpp \
       User.cpp \
       Book.cpp \
       PublicationRank.cpp \
       Journals.cpp

# Header files
HEADERS = functions.h \
          Library.h \
          LibraryItem.h \
          User.h \
          Book.h \
          PublicationRank.h \
          Journals.h

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = library_management_system

# Default target
all: $(TARGET)

# Rule to link object files to create the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile .cpp files into .o files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
