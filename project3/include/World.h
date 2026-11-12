#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Entity.h"
class World{
    private:
    std::vector<std::unique_ptr<Entity>> _world;
    public:
    void addEntity(std::unique_ptr<Entity> en){
        _world.push_back(std::move(en));
    }
    class iterator{
        private:
        using MyIterator=std::vector<std::unique_ptr<Entity>>::const_iterator;
        MyIterator _it;
        public:
        iterator(MyIterator it): _it(it){}
        Entity& operator*() const{
            return *(*_it);
        }
        Entity* operator->() const{
            return _it->get();
        }
        Entity* operator++(){
            ++_it;
            return _it->get();
        }
        bool operator!=(const iterator& other) const{
            return other._it!=_it;
        }
        bool operator==(const iterator& other) const{
            return _it==other._it;
        }


    };
    //мы сдвигаемся по памяти а не по контейнеру а у нас в entity храняться объукты разного размера, поэтому мы пишем операции для for для класса итератора
        
    iterator begin(){
            return iterator(_world.begin());
    }
    iterator end(){
        return iterator(_world.end());
    }
    void clear(){
        _world.clear();
    }
};
