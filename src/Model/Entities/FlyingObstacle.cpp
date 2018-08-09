#include "FlyingObstacle.h"
#include "Model/EventQueue.h"

namespace Model{

FlyingObstacle::FlyingObstacle(float x, float y, float health, float damage, float speed, float width, float height, string texture)
 : Enemy(x, y, health, damage, speed, width, height, texture){}

 FlyingObstacle::~FlyingObstacle(){}

void FlyingObstacle::update(){
  move();
}

void FlyingObstacle::move(){
  float tick     = 1.0f/60.0f;
  float distance = tick * getSpeed();
  auto position  = getPosition();

  setPosition(position.first - distance, position.second);
  //Destroy entity that leaves the playable and visible part of the world.
  if(getPosition().first < (-4.0f - getHalfWidth())){
    EventQueue::getInstance().addEnemyDeath(getID(), 0, 0);
  }
}

}
