#include "EnemyShooter.h"
#include "Model/EventQueue.h"

namespace Model{

EnemyShooter::EnemyShooter(float x, float y, float health, float damage, float speed, float width, float height, string texture)
 : Enemy(x, y, health, damage, speed, width, height, texture), shootingTime(60){}

 EnemyShooter::~EnemyShooter(){}

void EnemyShooter::update(){
  move();
  if(shootingTime == 0){
    shootingTime = 120;
    auto pos     = getPosition();
    EventQueue::getInstance().addEnemyFire("RedEnemyBullet", pos.first, pos.second);
  }
  else{
    shootingTime -= 1;
  }
}

void EnemyShooter::move(){
  float tick      = 1.0f/60.0f;
  float distanceX = tick * getSpeed();
  auto pos        = this->getPosition();
  setPosition(pos.first - distanceX, pos.second);

  //Destroy entity that leaves the playable and visible part of the world.
  if(getPosition().first < (-4.0f - getHalfWidth())){
    EventQueue::getInstance().addEnemyDeath(getID());
  }
}

}
