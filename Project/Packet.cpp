#include "Packet.h"

Packet::Packet(int size, int sourceId, int destinationId, double creationTime)
    : size(size), sourceId(sourceId), destinationId(destinationId),
      creationTime(creationTime), sendTime(0), receiveTime(0) {}

int Packet::getSize() const { return size; }

int Packet::getSourceId() const { return sourceId; }

int Packet::getDestinationId() const { return destinationId; }

double Packet::getCreationTime() const { return creationTime; }

void Packet::setSendTime(double time) { sendTime = time; }

void Packet::setReceiveTime(double time) { receiveTime = time; }

double Packet::getSendTime() const { return sendTime; }

double Packet::getReceiveTime() const { return receiveTime; }

double Packet::getLatency() const {
    if (receiveTime >= sendTime && sendTime >= creationTime) {
        return receiveTime - creationTime;
    } else {
        return 0;
    }
}
