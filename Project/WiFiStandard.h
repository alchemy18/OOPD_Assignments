#ifndef WIFISTANDARD_H
#define WIFISTANDARD_H

#include <vector>
#include "Device.h"
#include "FrequencyChannel.h"

class WiFiStandard {
protected:
    int users;
    double totalTime;         // Simulation time in milliseconds
    double throughput;        // Total throughput in Mbps
    double totalLatency;      // Sum of latencies in milliseconds
    double maxLatency;        // Maximum latency observed
    int totalPackets;         // Total packets transmitted
    std::vector<UserDevice*> userDevices;
    AccessPoint* accessPoint;
    FrequencyChannel channel;

public:
    WiFiStandard(int users);
    virtual ~WiFiStandard();
    virtual void simulateTransmission() = 0;
    void printMetrics();
};

class WiFi4 : public WiFiStandard {
public:
    WiFi4(int users);
    void simulateTransmission() override;
};

class WiFi5 : public WiFiStandard {
public:
    WiFi5(int users);
    void simulateTransmission() override;
};

class WiFi6 : public WiFiStandard {
public:
    WiFi6(int users);
    void simulateTransmission() override;
};

#endif // WIFISTANDARD_H
