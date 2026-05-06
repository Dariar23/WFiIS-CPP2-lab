#include "EventBus.h"

int EventBus::getEventCategory(EventType type){
    switch(type){
        case EventType::EnemyDamaged:
        case EventType::EnemyDied:
            return CatEnemy | CatSound;

        case EventType::PlayerHealed:
            return CatPlayer | CatSound;
        
        case EventType::ItemPicked:
            return CatLoot | CatSound;

        default:
        return 0;
    }
}
void EventBus::subscribe(Callback cb, int mask) {
    //m_callbacks.push_back(cb);
    m_subscribers.push_back({cb,mask});
}

// void EventBus::emit(std::unique_ptr<IEvent> event) {
//     m_events.push(std::move(event));
// }

void EventBus::emit(const Event& e) {
    m_events.push(e); 
}
void EventBus::destroyEvent(Event& e) {
    if(e.type == EventType::ItemPicked) {
        e.data.itemPicked.~ItemPickedData();
    }
}

void EventBus::processEvents() {
    while (!m_events.empty()) {
        // const std::unique_ptr<IEvent>& ev = m_events.front();
        // const IEvent& ref = *ev;

        // for (Callback cb : m_callbacks) {
        //     cb(ref);
        // }
         Event& e = m_events.front();
        int eventMask = getEventCategory(e.type);

        for (const auto& s : m_subscribers) {
            if (s.mask & eventMask) {
                s.cb(e);
            }
        }

        destroyEvent(e);
        m_events.pop();
    }
}
