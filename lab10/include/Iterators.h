#pragma once
#include<iostream>
#include<vector>
#include <functional>
namespace Iterators{
    class VectorIterator{
        private:
        const std::vector<int> &vec;
        std::function<bool(int)> filtry[5];
        int filt_count  =0;
        std::function<int(int)> mapy[5];
        int map_count =0;
        int max_take = -1;
        public:
        VectorIterator(const std::vector<int> &v) : vec(v){}
        VectorIterator& filter(std::function<bool(int)> f){
            if(filt_count < 5){
                filtry[filt_count++]= f;
            }
            return *this;
        }
        VectorIterator& map(std::function<int(int)> f){
            if(map_count<5){
                mapy[map_count++] =f;
            }
            return *this;
        }
        VectorIterator& take(int n){
            if(max_take==-1 || max_take > n){
                max_take = n;
            }
            return *this;
        }
        std::vector<int> collect(){

            std::vector<int> res;
            if(max_take>=0 ){
                res.reserve(max_take);
            }
            else{
                res.reserve(vec.size());
            }
            for(const auto& elem : vec) {
            
                if(max_take >= 0 ) {
                    break;
                }
                
                bool passed = true;
                for(int i = 0; i < filt_count; ++i) {
                    if (!filtry[i](elem)) {
                        passed = false;
                        break;
                    }
                }
                if(!passed) {
                    continue;
                }

                int value = elem;
                for(int i = 0; i < map_count; ++i) {
                    value = mapy[i](value);
                }
                
                res.push_back(value);
            }

            return res;

        }
        
    };
}