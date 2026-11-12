#pragma once
#include <string>

class NotificationChannel {
public:
    virtual ~NotificationChannel() = default;
    virtual void send(const std::string& target, const std::string& message) const = 0;
};