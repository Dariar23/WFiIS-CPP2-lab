#pragma once
#include <queue>
#include <vector>
#include <memory>
#include <string>


enum class EventType {
    EnemyDamaged,
    EnemyDied,
    PlayerHealed,
    ItemPicked
};

enum EventCategory{
    CatEnemy = 1 << 0,
    CatPlayer = 1 <<1,
    CatLoot = 1 <<2,
    CatSound = 1 <<3

};

// Konkretne eventy

 struct EnemyDamagedData {
    int enemyId;
    int damage;
    int remainingHp;

//     EnemyDamagedEvent(int id, int dmg, int hp): enemyId(id), damage(dmg), remainingHp(hp) {}

//     EventType type() const override {
//         return EventType::EnemyDamaged;
//     }
};

struct EnemyDiedData {
    int enemyId;
};

struct PlayerHealedData {
    int playerId;
    int amount;
    int newHp;
};

struct ItemPickedData {
    int playerId;
    std::string itemName;
    ItemPickedData() = default;
    ItemPickedData(int id, const std::string& name)
    : playerId(id), itemName(name) {}

};


union EventData{
    // EnemyDiedData enemyDied;
    // PlayerHealedData playerHeal;
    // ItemPickedData itemPicked;
    // EnemyDamagedData enemyDamaged;
    EnemyDamagedData enemyDamaged;
    EnemyDiedData enemyDied;
    PlayerHealedData playerHealed;
    ItemPickedData itemPicked;

    EventData(){}
    ~EventData(){}


};
struct Event {
    EventType type;
    EventData data;

    Event() = default;
    Event(const Event& other) {
        type = other.type;

        switch (type) {
            case EventType::EnemyDamaged:
                data.enemyDamaged = other.data.enemyDamaged;
                break;

            case EventType::EnemyDied:
                data.enemyDied = other.data.enemyDied;
                break;

            case EventType::PlayerHealed:
                data.playerHealed = other.data.playerHealed;
                break;

            case EventType::ItemPicked:
                new (&data.itemPicked)
                    ItemPickedData(other.data.itemPicked.playerId,
                                   other.data.itemPicked.itemName);
                break;
        }
    }

    ~Event() {
        if (type == EventType::ItemPicked) {
            data.itemPicked.~ItemPickedData();
        }
    }
};

using Callback = void(*)(const Event&);
struct Subscriber{
    Callback cb;
    int mask;
};
// EventBus

class EventBus {
    
public:

    void subscribe(Callback cb, int mask);
    void emit(const Event& e);
    void processEvents();

private:
    // std::queue<std::unique_ptr<IEvent>> m_events;
    // std::vector<Callback> m_callbacks;
    std::queue<Event> m_events;
    std::vector<Subscriber> m_subscribers;
    static int getEventCategory(EventType type);
    static void destroyEvent(Event&e);
};
