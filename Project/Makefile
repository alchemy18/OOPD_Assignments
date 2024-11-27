# Makefile for WiFi Simulator

CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2

SRC = main.cpp Device.cpp Packet.cpp FrequencyChannel.cpp WiFiStandard.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = wifi_simulator

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
