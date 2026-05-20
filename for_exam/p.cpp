#pragma once
#include <iostream>
#include <string>
class HttpChannel{
    public:
    void sendRequest(const std::string& url, const std::string& load) const {
        std::cout<<"HTTP request to "<<url<<": "<<load<<std::endl;

    }
};
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
#pragma once
#include <string>

class NotificationChannel {
public:
    virtual ~NotificationChannel() = default;
    virtual void send(const std::string& target, const std::string& message) const = 0;
};

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
#pragma once

#include <NotificationChannel.h>

class SmsChannel:public NotificationChannel{

    public:
    
    void send(const std::string& path, const std::string& message)const override{
        std::cout<<"SMS to: "<<path<<"->"<<message<<std::endl;
    }


};
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