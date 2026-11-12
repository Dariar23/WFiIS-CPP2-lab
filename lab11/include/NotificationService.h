#pragma once
#include "NotificationChannel.h"

class NotificationService {
private:
    const NotificationChannel* channel;
public:
    NotificationService(const NotificationChannel* ch) : channel(ch) {}
    
    void alert(const std::string& path, const std::string& message) const {
        channel->send(path, message);
    }
};