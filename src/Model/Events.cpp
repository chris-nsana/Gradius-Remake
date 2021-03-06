#include "Events.h"
#include "Model.h"
#include "EventQueue.h"

namespace Model{

Event::Event(){}

Event::~Event(){}

void Event::setModel(const std::shared_ptr<Model>& m){
  Event::model = m;
}

void Event::execute(){}

std::weak_ptr<Model> Event::model = std::weak_ptr<Model>();

EnemyDeath::EnemyDeath(int eID) : eID(eID){}

EnemyDeath::~EnemyDeath(){}

void EnemyDeath::execute(){
  if(auto spt = model.lock()){
    spt->destroyEntity(this->eID);
  }
}

FriendlyDeath::FriendlyDeath(int eID) : eID(eID){}

FriendlyDeath::~FriendlyDeath(){}

void FriendlyDeath::execute(){
  if(auto spt = model.lock()){
    spt->destroyEntity(this->eID);
  }
}

PlayerDeath::PlayerDeath(int eID, bool byEnemy) : eID(eID), byEnemy(byEnemy){}

PlayerDeath::~PlayerDeath(){}

void PlayerDeath::execute(){
  if(auto spt = model.lock()){
    if(byEnemy) {
      spt->decreasePlayerLives(eID, 1);
    }
    else {
      spt->decreasePlayerLives(eID, 2);
    }
    spt->destroyEntity(this->eID);
    //Freeze the model activity for 2 seconds without freezing the View
    spt->freeze(2.0f, false);
    //Add an event to reset the level after the wait is over.
    EventQueue::getInstance().addLevelReset();
  }
}

BossDeath::BossDeath(){}

BossDeath::~BossDeath(){}

void BossDeath::execute(){
  if(auto spt = model.lock()){
    //Freeze the model activity for 2 seconds without freezing the View
    spt->freeze(2.0f, false);
    //Add an event to start the next level
    EventQueue::getInstance().addLevelEnd();
  }
}

PlayerFire::PlayerFire(int shooterID, std::string entity, float x, float y) : shooterID(shooterID), entity(entity), x(x), y(y){}

PlayerFire::~PlayerFire(){}

void PlayerFire::execute(){
  if(auto spt = model.lock()){
    spt->createEntity(this->entity, this->x, this->y, this->shooterID);
  }
}

EnemyFire::EnemyFire(std::string entity, float x, float y) : entity(entity), x(x), y(y){}

EnemyFire::~EnemyFire(){}

void EnemyFire::execute(){
  if(auto spt = model.lock()){
    spt->createEntity(this->entity, this->x, this->y);
  }
}

PointsGain::PointsGain(int scorerID, int amount) : scorerID(scorerID), amount(amount){}

PointsGain::~PointsGain(){}

void PointsGain::execute(){
  if(auto spt = model.lock()){
    spt->addPoints(scorerID, amount);
  }
}

LevelReset::LevelReset(){}

LevelReset::~LevelReset(){}

void LevelReset::execute(){
  if(auto spt = model.lock()){
    spt->resetLevel();
  }
}

LevelEnd::LevelEnd(){}

LevelEnd::~LevelEnd(){}

void LevelEnd::execute(){
  if(auto spt = model.lock()){
    spt->startNextLevel();
  }
}

}
