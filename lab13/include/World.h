#pragma once
#include <vector>
#include <memory>
#include "Entity.h"

enum class EntityType {
    ALL,
    NPC,
    PLAYER,
    TREE
};

class World {
private:
    std::vector<std::unique_ptr<Entity>> _entities;
    
public:
    void addEntity(std::unique_ptr<Entity> entity) {
        _entities.push_back(std::move(entity));
    }
    
   
    class Iterator {
    private:
        using VecIter = std::vector<std::unique_ptr<Entity>>::const_iterator;
        
        VecIter _it;
        VecIter _end;
        EntityType _filter;
        
        void skipToNext() {
            while (_it != _end && !matchesFilter(_it->get())) {
                ++_it;
            }
        }
        
        bool matchesFilter(Entity* entity) const {
            if(_filter == EntityType::ALL){
                return true;
            } 
            
            if(_filter == EntityType::NPC){
                return dynamic_cast<NPC*>(entity) != nullptr;
            } 
            if(_filter == EntityType::PLAYER){
                return dynamic_cast<Player*>(entity) != nullptr;
            } 
            if(_filter == EntityType::TREE){
                return dynamic_cast<Tree*>(entity) != nullptr;
            }
            
            return false;
        }
        
    public:
        Iterator(VecIter it, VecIter end, EntityType filter = EntityType::ALL) 
            : _it(it), _end(end), _filter(filter) {
            skipToNext();
        }
        
        Entity* operator->() const { 
            return _it->get(); 
        }
        
        Entity& operator*() const { 
            return *(*_it); 
        }
        
        Iterator& operator++() {
            ++_it;
            skipToNext();
            return *this;
        }
        
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        
        bool operator==(const Iterator& other) const { 
            return _it == other._it; 
        }
        
        bool operator!=(const Iterator& other) const { 
            return _it != other._it; 
        }
    };
    
    Iterator begin(EntityType filter = EntityType::ALL) const {
        return Iterator(_entities.begin(), _entities.end(), filter);
    }
    
    Iterator end() const { 
        return Iterator(_entities.end(), _entities.end(), EntityType::ALL);
    }
    
    Iterator entityTypeIterator(EntityType type) const {
        return Iterator(_entities.begin(), _entities.end(), type);
    }
    
    void clear() { 
        _entities.clear(); 
    }
};