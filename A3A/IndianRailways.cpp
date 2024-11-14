// IndianRailways.cpp

#include "IndianRailways.h"

Platform::Platform(int number, int interval) : platformNumber(number) {
    if (interval != 10 && interval != 30) {
        throw std::invalid_argument("Invalid stop interval. Must be 10 or 30 minutes.");
    }
    stopInterval = interval;
}

int Platform::getStopInterval() const {
    return stopInterval;
}

int Platform::getPlatformNumber() const {
    return platformNumber;
}

Line::Line(const std::string& name, bool throughTrain) : lineName(name), isThroughTrain(throughTrain) {}

std::string Line::getLineName() const {
    return lineName;
}

bool Line::isThrough() const {
    return isThroughTrain;
}

template<typename T>
Station<T>::Station(T id) : stationID(id) {}

template<typename T>
T Station<T>::getStationID() const {
    return stationID;
}

template<typename T>
void Station<T>::addLine(const Line& line) {
    lines.push_back(line);
}

template<typename T>
void Station<T>::addPlatform(const Platform& platform) {
    platforms.push_back(platform);
}

template<typename T>
void Station<T>::showStationInfo() const {
    std::cout << "Station ID: " << stationID << std::endl;
    std::cout << "Lines connected:" << std::endl;
    for (const auto& line : lines) {
        std::cout << " - " << line.getLineName() << " (Through train: " << (line.isThrough() ? "Yes" : "No") << ")" << std::endl;
    }
    std::cout << "Platforms available:" << std::endl;
    for (const auto& platform : platforms) {
        std::cout << " - Platform " << platform.getPlatformNumber() << " with stop interval: " << platform.getStopInterval() << " minutes" << std::endl;
    }
}

int getValidIntegerInput(const std::string& prompt, int minValue, int maxValue) {
    int input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;
        if (std::cin.fail() || input < minValue || input > maxValue) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer between " << minValue << " and " << maxValue << "." << std::endl;
        } else {
            return input;
        }
    }
}

std::string getValidStringInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::cin.ignore();
    std::getline(std::cin, input);
    return input;
}

// Explicit template instantiation for int Station
template class Station<int>;
