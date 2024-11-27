#include <iostream>
#include "WiFiStandard.h"

int main(int argc, char* argv[]) {
    int numUsers = 10; // Default number of users

    if (argc > 1) {
        numUsers = std::stoi(argv[1]);
    }

    std::cout << "WiFi 4 Simulation with " << numUsers << " Users:\n";
    WiFi4 wifi4(numUsers);
    wifi4.simulateTransmission();
    wifi4.printMetrics();

    std::cout << "\nWiFi 5 Simulation with " << numUsers << " Users:\n";
    WiFi5 wifi5(numUsers);
    wifi5.simulateTransmission();
    wifi5.printMetrics();

    std::cout << "\nWiFi 6 Simulation with " << numUsers << " Users:\n";
    WiFi6 wifi6(numUsers);
    wifi6.simulateTransmission();
    wifi6.printMetrics();

    return 0;
}
