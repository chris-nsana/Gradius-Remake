#include "EnemyBullet.h"
#include "Model/EventQueue.h"

namespace Model{

EnemyBullet::EnemyBullet(float x, float y, float health, float damage, float speed, float width, float height, string texture)
 : Enemy(x, y, health, damage, speed, width, height, texture){}

 EnemyBullet::~EnemyBullet(){}

void EnemyBullet::update(){
  move();
}

void EnemyBullet::move(){
  float tick      = 1.0f/60.0f;
  float distanceX = tick * getSpeed();
  auto pos        = this->getPosition();
  setPosition(pos.first - distanceX, pos.second);

  //Destroy entity that leaves the playable and visible part of the world.
  if(getPosition().first < (-4.0f - getHalfWidth())){
    EventQueue::getInstance().addEnemyDeath(getID(), 0, 0);
  }
}

}
