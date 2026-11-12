#pragma once
#include <vector>
#include "NotificationChannel.h"  

class MultiChannel : public NotificationChannel { 
private:
    std::vector<const NotificationChannel*> channels;
public:
    void addChannel(const NotificationChannel* channel) { 
        channels.push_back(channel);
    }
    
    void send(const std::string& target, const std::string& message) const override {
        for (const auto& channel : channels) {
            channel->send(target, message);
        }
    }
};