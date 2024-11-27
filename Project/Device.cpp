#include "Device.h"
#include <iostream>

Device::Device(int id, std::string type) : id(id), type(type), busy(false) {}

int Device::getId() const { return id; }

std::string Device::getType() const { return type; }

bool Device::isBusy() const { return busy; }

void Device::setBusy(bool state) { busy = state; }

void Device::enqueuePacket(const Packet& pkt) {
    packetQueue.push(pkt);
}

bool Device::hasPackets() const {
    return !packetQueue.empty();
}

Packet Device::getNextPacket() {
    if (packetQueue.empty()) {
        throw std::runtime_error("Packet queue is empty.");
    }
    Packet pkt = packetQueue.front();
    packetQueue.pop();
    return pkt;
}

// UserDevice Implementation

UserDevice::UserDevice(int id) : Device(id, "User") {}

void UserDevice::sendPacket(Packet& pkt) {
    // Implement user-specific packet sending logic if necessary
}

void UserDevice::receivePacket(const Packet& pkt) {
    // Implement user-specific packet receiving logic if necessary
}

// AccessPoint Implementation

AccessPoint::AccessPoint() : Device(0, "AP") {}

void AccessPoint::sendPacket(Packet& pkt) {
    // Implement AP-specific packet sending logic if necessary
}

void AccessPoint::receivePacket(const Packet& pkt) {
    // Implement AP-specific packet receiving logic if necessary
}
