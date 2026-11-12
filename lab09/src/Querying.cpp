#include <iostream>

#include "Querying.h"


Querying::CompositeQuery::~CompositeQuery(){
    for(auto q: queries){
        delete q;
    }
 }
        //constructor copy
Querying::CompositeQuery::CompositeQuery(const CompositeQuery& other): size(other.size){
    
    queries.reserve(size);
    for( auto q: other.queries){
        queries.push_back(q->clone());
    }
}

Querying::CompositeQuery& Querying::CompositeQuery::operator=(const CompositeQuery& other){
    if(this==&other){
        return *this;
    }
    
    for(auto q: queries){
        delete q;
    }
    queries.clear();
    size=other.size;
    queries.reserve(size);
    for(auto q: other.queries){
        queries.push_back(q->clone());
    }
        
        return *this;
}
std::vector<int> Querying::filter(const std::vector<int>& data,const CompositeQuery& queries ){
        std::vector<int> res;
        for( size_t i=0; i <data.size(); i++){
            if(queries.matches(data[i])){
                res.push_back(data[i]);
            }
        }
        return res;
    }