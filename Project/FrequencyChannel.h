#ifndef FREQUENCYCHANNEL_H
#define FREQUENCYCHANNEL_H

#include <vector>
#include <string>
#include <map>

class FrequencyChannel {
private:
    bool busy;
    std::map<int, bool> subChannels; // Sub-channel ID and availability

public:
    FrequencyChannel();
    bool isBusy() const;
    void setBusy(bool state);
    void allocateSubChannel(int subChannelId);
    void releaseSubChannel(int subChannelId);
    bool isSubChannelAvailable(int subChannelId) const;
    std::vector<int> getAvailableSubChannels() const;
};

#endif // FREQUENCYCHANNEL_H
