#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_
#include "Utilities/Singleton.h"
#include <queue>

class Event;

namespace Model{

class EventQueue : public utils::Singleton<Stopwatch>{

public:

  void addSmt();

  bool isEmpty();

  void addDeath(int smt);

  void addPlayerDeath(int smt);

  void addBossDeath(int smt);

  void addBulletFire(int smt);

  std::unique_ptr<Event> dequeue();

private:

  std::queue<std::unique_ptr<Event>> container;


}

}


#endif /* EVENTQUEUE_H_ */
