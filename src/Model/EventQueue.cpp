#include "EventQueue.h"
#include<iostream>


namespace Model{

bool EventQueue::isEmpty(){
  return container.empty();
}

int  EventQueue::getSize(){
  return container.size();
}

void EventQueue::clear(){
  container = {};
}

void EventQueue::addEnemyDeath(int eID){
  std::unique_ptr<Event> e = std::make_unique<EnemyDeath>(eID);
  container.push(std::move(e));
}

void EventQueue::addFriendlyDeath(int eID){
  std::unique_ptr<Event> e = std::make_unique<FriendlyDeath>(eID);
  container.push(std::move(e));
}

void EventQueue::addPlayerDeath(int eID, bool byEnemy){
  std::unique_ptr<Event> e = std::make_unique<PlayerDeath>(eID, byEnemy);
  container.push(std::move(e));
}

void EventQueue::addBossDeath(){
  std::unique_ptr<Event> e = std::make_unique<BossDeath>();
  container.push(std::move(e));
}

void EventQueue::addPlayerFire(int shooterID, std::string entity, float x, float y){
  std::unique_ptr<Event> e = std::make_unique<PlayerFire>(shooterID, entity, x, y);
  container.push(std::move(e));
}

void EventQueue::addEnemyFire(std::string entity, float x, float y){
  std::unique_ptr<Event> e = std::make_unique<EnemyFire>(entity, x, y);
  container.push(std::move(e));
}

void EventQueue::addPointsGain(int id, int amount){
  std::unique_ptr<Event> e = std::make_unique<PointsGain>(id, amount);
  container.push(std::move(e));
}

void EventQueue::addLevelReset(){
  std::unique_ptr<Event> e = std::make_unique<LevelReset>();
  container.push(std::move(e));
}

void EventQueue::addLevelEnd(){
  std::unique_ptr<Event> e = std::make_unique<LevelEnd>();
  container.push(std::move(e));
}

std::unique_ptr<Event> EventQueue::dequeue(){
  auto eptr = std::move(container.front());
  container.pop();
  return eptr;
}

}
