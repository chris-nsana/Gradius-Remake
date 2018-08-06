#include "EnemyGrunt.h"
#include "Model/EventQueue.h"

namespace Model{

EnemyGrunt::EnemyGrunt(float x, float y, float health, float damage, float speed, float width, float height, string texture)
 : Enemy(x, y, health, damage, speed, width, height, texture){}

 EnemyGrunt::~EnemyGrunt(){}


void EnemyGrunt::update(){
  move();
}

void EnemyGrunt::move(){
  float tick     = 1.0f/60.0f;
  float distance = tick * getSpeed();
  auto pos       = this->getPosition();
  setPosition(pos.first - distance, pos.second);
  //Destroy entity that leaves the playable and visible part of the world.
  if(getPosition().first < (-4.0f - getHalfWidth())){
    EventQueue::getInstance().addEnemyDeath(getID(), 0, 0);
  }
}
}
