#pragma once
#include "NotificationChannel.h"
#include "HttpChannel.h"
class TeamsChannel :public NotificationChannel{
    private:
    HttpChannel httpChannel;
    public:
    void send(const std::string& url, const std::string& message)const override{
       std::string payload = "group=" + url + "&text=" + message;
        httpChannel.sendRequest("https://teams.example/send", payload);
    }
};