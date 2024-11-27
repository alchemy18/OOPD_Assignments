#ifndef PACKET_H
#define PACKET_H

#include <string>

class Packet {
private:
    int size;           // in bytes
    int sourceId;
    int destinationId;
    double creationTime; // timestamp when the packet was created
    double sendTime;     // timestamp when the packet was sent
    double receiveTime;  // timestamp when the packet was received

public:
    Packet(int size, int sourceId, int destinationId, double creationTime);
    int getSize() const;
    int getSourceId() const;
    int getDestinationId() const;
    double getCreationTime() const;
    void setSendTime(double time);
    void setReceiveTime(double time);
    double getSendTime() const;
    double getReceiveTime() const;
    double getLatency() const;
};

#endif // PACKET_H
