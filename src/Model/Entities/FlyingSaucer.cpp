#include "FlyingSaucer.h"
#include "Model/EventQueue.h"

namespace Model{

FlyingSaucer::FlyingSaucer(float x, float y, float health, float damage, float speed, float width, float height, string texture)
 : Enemy(x, y, health, damage, speed, width, height, texture), moveUpward(true){}

 FlyingSaucer::~FlyingSaucer(){}

void FlyingSaucer::update(){
  move();
}

void FlyingSaucer::move(){
  float tick      = 1.0f/60.0f;
  float distanceX = tick * getSpeed();
  float distanceY = 0.50f * distanceX;
  auto pos        = this->getPosition();
  if(!moveUpward) distanceY *= (-1);
  setPosition(pos.first - distanceX, pos.second + distanceY);

  //If the Saucer flew high enough upward it needs to fly downward
  if((getPosition().second + getHalfHeight())>= 2.80 ) moveUpward = false;
  //If the Saucer flew low enough it needs to fly upwrd
  else if(((getPosition().second - getHalfHeight()) <= 2.80 )) moveUpward = true;
  //Destroy entity that leaves the playable and visible part of the world.
  if(getPosition().first < (-4.0f - getHalfWidth())){
    EventQueue::getInstance().addEnemyDeath(getID(), 0, 0);
  }
}

}
