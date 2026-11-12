#pragma once
#include "NotificationChannel.h"
#include "HttpChannel.h"
class SlackChannel :public NotificationChannel{
    private:
    HttpChannel httpChannel;
    public:
    void send(const std::string& url, const std::string& message) const override{
        std::string load="channel="+url+message;
        httpChannel.sendRequest("https://slack.example/send", load);
    }
};