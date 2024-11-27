#include "FrequencyChannel.h"

FrequencyChannel::FrequencyChannel() : busy(false) {
    // Initialize sub-channels (Assuming 10 sub-channels)
    for (int i = 1; i <= 10; ++i) {
        subChannels[i] = true; // All sub-channels are initially available
    }
}

bool FrequencyChannel::isBusy() const { return busy; }

void FrequencyChannel::setBusy(bool state) { busy = state; }

void FrequencyChannel::allocateSubChannel(int subChannelId) {
    subChannels[subChannelId] = false;
}

void FrequencyChannel::releaseSubChannel(int subChannelId) {
    subChannels[subChannelId] = true;
}

bool FrequencyChannel::isSubChannelAvailable(int subChannelId) const {
    auto it = subChannels.find(subChannelId);
    if (it != subChannels.end()) {
        return it->second;
    }
    return false;
}

std::vector<int> FrequencyChannel::getAvailableSubChannels() const {
    std::vector<int> available;
    for (const auto& sc : subChannels) {
        if (sc.second) {
            available.push_back(sc.first);
        }
    }
    return available;
}

