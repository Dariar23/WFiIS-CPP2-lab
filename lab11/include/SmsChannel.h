#pragma once

#include <NotificationChannel.h>

class SmsChannel:public NotificationChannel{

    public:
    
    void send(const std::string& path, const std::string& message)const override{
        std::cout<<"SMS to: "<<path<<"->"<<message<<std::endl;
    }


};