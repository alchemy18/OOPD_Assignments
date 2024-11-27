#ifndef DEVICE_H
#define DEVICE_H

#include <queue>
#include "Packet.h"

class Device {
protected:
    int id;
    std::string type; // "User" or "AP"
    bool busy;
    std::queue<Packet> packetQueue;

public:
    Device(int id, std::string type);
    virtual ~Device() {}
    int getId() const;
    std::string getType() const;
    bool isBusy() const;
    void setBusy(bool state);
    void enqueuePacket(const Packet& pkt);
    bool hasPackets() const;
    Packet getNextPacket();
    virtual void sendPacket(Packet& pkt) = 0;
    virtual void receivePacket(const Packet& pkt) = 0;
};

class UserDevice : public Device {
public:
    UserDevice(int id);
    void sendPacket(Packet& pkt) override;
    void receivePacket(const Packet& pkt) override;
};

class AccessPoint : public Device {
public:
    AccessPoint();
    void sendPacket(Packet& pkt) override;
    void receivePacket(const Packet& pkt) override;
};

#endif // DEVICE_H
