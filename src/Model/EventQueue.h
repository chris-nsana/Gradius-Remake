#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_
#include "Utilities/Singleton.h"
#include "Events.h"
#include <queue>

class Event;

namespace Model{

class EventQueue : public utils::Singleton<EventQueue>{
  friend Singleton<EventQueue>;

public:

  bool isEmpty();

  int getSize();

  void clear();

  void addEnemyDeath(int eID);

  void addEnemyDeath(int eID, int killerID, int worth);

  void addFriendlyDeath(int eID);

  void addPlayerDeath(int eID);

  void addBossDeath(int eID, int worth);

  void addPlayerFire(int shooterID, std::string entity, float x, float y);

  void addEnemyFire(std::string entity, float x, float y);

  void addPointsGain(int id, int amount);

  void addLevelReset();

  std::unique_ptr<Event> dequeue();

private:

  EventQueue()=default;
  ~EventQueue()=default;
  EventQueue& operator=(const EventQueue&)=default;

  std::queue<std::unique_ptr<Event>> container;

};

}
#endif /* EVENTQUEUE_H_ */
