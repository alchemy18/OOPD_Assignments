# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall
DEBUGFLAGS = -g
OPTFLAGS = -O2
SRCDIR = src
OBJDIR = obj
INCLUDE = -I$(SRCDIR)
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
EXEC = publication_manager

# Targets
all: debug optimized

debug: CXXFLAGS += $(DEBUGFLAGS)
debug: $(EXEC)_debug

optimized: CXXFLAGS += $(OPTFLAGS)
optimized: $(EXEC)_optimized

$(EXEC)_debug: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(EXEC)_optimized: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(EXEC)_debug $(EXEC)_optimized
