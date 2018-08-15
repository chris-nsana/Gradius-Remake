#include "SaucerBoss.h"
#include "Model/EventQueue.h"

namespace Model{

SaucerBoss::SaucerBoss(float x, float y, float health, float damage, float speed, float width, float height, string texture)
 : Enemy(x, y, health, damage, speed, width, height, texture), moveForward(true), spawnTime(60){}

 SaucerBoss::~SaucerBoss(){}

void SaucerBoss::takeDamage(float amount, bool enemy){
  Enemy::takeDamage(amount, enemy);
  if(isDead()) EventQueue::getInstance().addBossDeath();
}

void SaucerBoss::update(){
  move();
  if(spawnTime == 0){
    spawnTime = 60;
    //Create FlyingSaucer enemies to aid the boss.
    EventQueue::getInstance().addEnemyFire("FlyingSaucer", 5.0f, 2.0f);
    EventQueue::getInstance().addEnemyFire("FlyingSaucer", 5.0f, -2.0f);
  }
  else{
    spawnTime -= 1;
  }
}

void SaucerBoss::move(){
  float tick      = 1.0f/60.0f;
  float distanceX = tick * getSpeed();
  auto pos        = this->getPosition();
  if(!moveForward) distanceX = -distanceX;
  setPosition(pos.first - distanceX, pos.second);

  //If the Boss reached the center of the field move back
  if(getPosition().first  - getHalfWidth() <= -4.0f) this->moveForward = false;
  //If the Boss reached the left edge of the field move forward
  else if(getPosition().first + getHalfWidth() >= 4.0f ) moveForward = true;
}

}
