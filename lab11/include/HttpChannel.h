#pragma once
#include <iostream>
#include <string>
class HttpChannel{
    public:
    void sendRequest(const std::string& url, const std::string& load) const {
        std::cout<<"HTTP request to "<<url<<": "<<load<<std::endl;

    }
};