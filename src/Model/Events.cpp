#include "Events.h"
#include "Model.h"

namespace Model{

Event::Event(){}

Event::~Event(){}

void Event::setModel(const std::shared_ptr<Model>& m){
  Event::model = m;
}

void Event::execute(){}

std::weak_ptr<Model> Event::model = std::weak_ptr<Model>();

EnemyDeath::EnemyDeath(int eID, int killerID, int worth) : eID(eID), killerID(killerID), worth(worth){}

EnemyDeath::~EnemyDeath(){}

void EnemyDeath::execute(){
  return void();
}

FriendlyDeath::FriendlyDeath(int eID) : eID(eID){}

FriendlyDeath::~FriendlyDeath(){}

void FriendlyDeath::execute(){
  return void();
}

PlayerDeath::PlayerDeath(int eID) : eID(eID){}

PlayerDeath::~PlayerDeath(){}

void PlayerDeath::execute(){
  return void();
}

BossDeath::BossDeath(int eID, int worth) : eID(eID), worth(worth){}

BossDeath::~BossDeath(){}

void BossDeath::execute(){
  return void();
}

PlayerFire::PlayerFire(int shooterID, std::string entity, float x, float y) : shooterID(shooterID), entity(entity), x(x), y(y){}

PlayerFire::~PlayerFire(){}

void PlayerFire::execute(){
  if(auto spt = model.lock()){
    spt->createEntity(this->entity, this->x, this->y);
  }
}

EnemyFire::EnemyFire(std::string entity, float x, float y) : entity(entity), x(x), y(y){}

EnemyFire::~EnemyFire(){}

void EnemyFire::execute(){
  return void();
}

}
