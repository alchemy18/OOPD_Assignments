#include "WiFiStandard.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <queue>

// Constants
const double BANDWIDTH = 20e6;      // 20 MHz
const double MODULATION_RATE = 8;   // 256-QAM: 8 bits per symbol
const double CODING_RATE = 5.0 / 6.0;
const int PACKET_SIZE = 1000;       // 1 KB = 1000 bytes
const double MAX_SIMULATION_TIME = 1e3; // in milliseconds (1 second)

// Utility for random backoff
int getRandomBackoff(int maxBackoff) {
    static std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, maxBackoff);
    return distribution(generator);
}

// Base WiFiStandard Implementation

WiFiStandard::WiFiStandard(int users) : users(users), totalTime(0), throughput(0),
                                        totalLatency(0), maxLatency(0), totalPackets(0) {
    // Create user devices
    for (int i = 1; i <= users; ++i) {
        userDevices.push_back(new UserDevice(i));
    }
    accessPoint = new AccessPoint();
}

WiFiStandard::~WiFiStandard() {
    for (auto user : userDevices) {
        delete user;
    }
    delete accessPoint;
}

void WiFiStandard::printMetrics() {
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Throughput: " << throughput << " Mbps\n";
    std::cout << "Average Latency: "
              << (totalPackets > 0 ? totalLatency / totalPackets : 0) << " ms\n";
    std::cout << "Maximum Latency: " << maxLatency << " ms\n";
}

// WiFi 4 Implementation

WiFi4::WiFi4(int users) : WiFiStandard(users) {}

void WiFi4::simulateTransmission() {
    const int MAX_BACKOFF = 10; // Max backoff time in ms
    double time = 0;
    int successfulPackets = 0;
    std::vector<int> backoffTimes(users, 0);
    std::vector<double> nextAttemptTimes(users, 0);

    while (time < MAX_SIMULATION_TIME) {
        // Check if any user is ready to transmit
        for (int i = 0; i < users; ++i) {
            if (nextAttemptTimes[i] <= time) {
                if (!channel.isBusy()) {
                    // Channel is free, transmit packet
                    channel.setBusy(true);
                    double transmissionTime = (PACKET_SIZE * 8) /
                                              (BANDWIDTH * MODULATION_RATE * CODING_RATE) * 1e3; // ms
                    Packet pkt(PACKET_SIZE, userDevices[i]->getId(), accessPoint->getId(), time);
                    pkt.setSendTime(time);
                    pkt.setReceiveTime(time + transmissionTime);
                    totalLatency += pkt.getLatency();
                    maxLatency = std::max(maxLatency, pkt.getLatency());
                    successfulPackets++;
                    totalTime += transmissionTime;
                    totalPackets++;

                    // Schedule next attempt after transmission
                    nextAttemptTimes[i] = time + transmissionTime;
                    channel.setBusy(false);
                } else {
                    // Channel is busy, backoff
                    int backoff = getRandomBackoff(MAX_BACKOFF);
                    nextAttemptTimes[i] = time + backoff;
                }
            }
        }
        time += 0.1; // Increment time by 0.1 ms
    }
    throughput = (successfulPackets * PACKET_SIZE * 8) / (MAX_SIMULATION_TIME * 1e3); // Mbps
}

// WiFi 5 Implementation

WiFi5::WiFi5(int users) : WiFiStandard(users) {}

void WiFi5::simulateTransmission() {
    const int CSI_PACKET_SIZE = 200; // Bytes
    const int COMMUNICATION_TIME = 15; // ms
    double time = 0;
    int successfulPackets = 0;

    while (time < MAX_SIMULATION_TIME) {
        // AP broadcasts a packet
        double broadcastTime = (CSI_PACKET_SIZE * 8) /
                               (BANDWIDTH * MODULATION_RATE * CODING_RATE) * 1e3; // ms
        time += broadcastTime;

        // Users send CSI sequentially
        double csiTimePerUser = (CSI_PACKET_SIZE * 8) /
                                (BANDWIDTH * MODULATION_RATE * CODING_RATE) * 1e3; // ms
        time += users * csiTimePerUser;

        // Parallel communication
        double dataTransmissionTime = COMMUNICATION_TIME;
        double transmissionTimePerPacket = (PACKET_SIZE * 8) /
                                           (BANDWIDTH * MODULATION_RATE * CODING_RATE) * 1e3; // ms
        int packetsPerUser = dataTransmissionTime / transmissionTimePerPacket;

        for (int i = 0; i < users; ++i) {
            for (int p = 0; p < packetsPerUser; ++p) {
                Packet pkt(PACKET_SIZE, accessPoint->getId(), userDevices[i]->getId(), time);
                pkt.setSendTime(time);
                pkt.setReceiveTime(time + transmissionTimePerPacket);
                totalLatency += pkt.getLatency();
                maxLatency = std::max(maxLatency, pkt.getLatency());
                successfulPackets++;
                totalPackets++;
                time += transmissionTimePerPacket;
            }
        }
        // Total time includes communication time
        time += dataTransmissionTime;
    }
    throughput = (successfulPackets * PACKET_SIZE * 8) / (MAX_SIMULATION_TIME * 1e3); // Mbps
}

// WiFi 6 Implementation

WiFi6::WiFi6(int users) : WiFiStandard(users) {}

void WiFi6::simulateTransmission() {
    const int SUB_CHANNEL_WIDTH = 2e6; // 2 MHz sub-channels
    const int SUB_CHANNELS = 10;       // Total sub-channels in 20 MHz
    const int COMMUNICATION_TIME = 5;  // ms
    double time = 0;
    int successfulPackets = 0;
    int userIndex = 0;

    while (time < MAX_SIMULATION_TIME) {
        // Allocate sub-channels to users in round-robin fashion
        std::vector<int> allocatedUsers;
        for (int sc = 0; sc < SUB_CHANNELS && userIndex < users; ++sc) {
            allocatedUsers.push_back(userIndex);
            userIndex = (userIndex + 1) % users;
        }

        // Users transmit in parallel on allocated sub-channels
        double transmissionTimePerPacket = (PACKET_SIZE * 8) /
                                           (SUB_CHANNEL_WIDTH * MODULATION_RATE * CODING_RATE) * 1e3; // ms
        int packetsPerUser = COMMUNICATION_TIME / transmissionTimePerPacket;

        for (int uid : allocatedUsers) {
            for (int p = 0; p < packetsPerUser; ++p) {
                Packet pkt(PACKET_SIZE, userDevices[uid]->getId(), accessPoint->getId(), time);
                pkt.setSendTime(time);
                pkt.setReceiveTime(time + transmissionTimePerPacket);
                totalLatency += pkt.getLatency();
                maxLatency = std::max(maxLatency, pkt.getLatency());
                successfulPackets++;
                totalPackets++;
                time += transmissionTimePerPacket;
            }
        }
        time += COMMUNICATION_TIME;
    }
    throughput = (successfulPackets * PACKET_SIZE * 8) / (MAX_SIMULATION_TIME * 1e3); // Mbps
}
