// main.cpp

#include "IndianRailways.h"
#include <vector>

void displayMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Add a Station\n";
    std::cout << "2. View Station Information\n";
    std::cout << "3. View All Stations\n";
    std::cout << "4. Exit\n";
}

int main() {
    std::vector<Station<int>> stations;  // List to store stations
    bool running = true;

    while (running) {
        displayMenu();
        int choice = getValidIntegerInput("Enter your choice: ", 1, 4);

        switch (choice) {
            case 1: {
                // Add a new station
                int stationID = getValidIntegerInput("Enter Station ID (integer): ", 100, 999);
                Station<int> newStation(stationID);

                // Add lines dynamically
                bool addingLines = true;
                while (addingLines) {
                    std::string lineName = getValidStringInput("Enter name for a new Line: ");
                    bool isThrough = getValidIntegerInput("Is this line a through train? (1 for Yes, 0 for No): ", 0, 1) == 1;
                    newStation.addLine(Line(lineName, isThrough));

                    char addMoreLines = getValidStringInput("Do you want to add another line? (y/n): ")[0];
                    if (addMoreLines == 'n' || addMoreLines == 'N') {
                        addingLines = false;
                    }
                }

                // Add platforms dynamically with numbering
                bool addingPlatforms = true;
                int platformCount = 1;  // Platform numbers start from 1
                while (addingPlatforms) {
                    int platformInterval = getValidIntegerInput("Enter platform stop interval (10 or 30 minutes): ", 10, 30);
                    newStation.addPlatform(Platform(platformCount, platformInterval));
                    platformCount++;  // Increment platform number for the next platform

                    char addMorePlatforms = getValidStringInput("Do you want to add another platform? (y/n): ")[0];
                    if (addMorePlatforms == 'n' || addMorePlatforms == 'N') {
                        addingPlatforms = false;
                    }
                }

                // Add station to list
                stations.push_back(newStation);
                std::cout << "Station added successfully.\n";
                break;
            }
            case 2: {
                // View information of a specific station
                int stationID = getValidIntegerInput("Enter the Station ID to view its details: ", 100, 999);
                bool found = false;
                for (const auto& station : stations) {
                    if (station.getStationID() == stationID) {
                        station.showStationInfo();
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << "Station with ID " << stationID << " not found.\n";
                }
                break;
            }
            case 3: {
                // View all stations
                if (stations.empty()) {
                    std::cout << "No stations added yet.\n";
                } else {
                    std::cout << "All Stations Information:\n";
                    for (const auto& station : stations) {
                        station.showStationInfo();
                        std::cout << "------------------------------\n";
                    }
                }
                break;
            }
            case 4:
                // Exit the program
                running = false;
                std::cout << "Exiting program...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}