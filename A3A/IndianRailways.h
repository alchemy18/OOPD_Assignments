// IndianRailways.h

#ifndef INDIANRAILWAYS_H
#define INDIANRAILWAYS_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits>

class Platform {
private:
    int platformNumber;
    int stopInterval;

public:
    Platform(int number, int interval);
    int getStopInterval() const;
    int getPlatformNumber() const;
};

class Line {
private:
    std::string lineName;
    bool isThroughTrain;

public:
    Line(const std::string& name, bool throughTrain);
    std::string getLineName() const;
    bool isThrough() const;
};

template<typename T>
class Station {
private:
    T stationID;
    std::vector<Line> lines;
    std::vector<Platform> platforms;

public:
    Station(T id);
    T getStationID() const;
    void addLine(const Line& line);
    void addPlatform(const Platform& platform);
    void showStationInfo() const;
};

int getValidIntegerInput(const std::string& prompt, int minValue, int maxValue);
std::string getValidStringInput(const std::string& prompt);

#endif // INDIANRAILWAYS_H
