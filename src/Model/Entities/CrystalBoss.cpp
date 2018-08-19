#include "CrystalBoss.h"
#include "Model/EventQueue.h"

namespace Model{

CrystalBoss::CrystalBoss(float x, float y, float health, float damage, float speed, float width, float height, string texture)
 : Enemy(x, y, health, damage, speed, width, height, texture), shootingTime(145), standStill(0), moveUpward(true){}

 CrystalBoss::~CrystalBoss(){}

void CrystalBoss::takeDamage(float amount, bool enemy){
  Enemy::takeDamage(amount, enemy);
  if(isDead()) EventQueue::getInstance().addBossDeath();
}

void CrystalBoss::update(){
  move();
  if(shootingTime == 0){
    shootingTime = 145;
    standStill   = 10;
    auto pos = getPosition();
    EventQueue::getInstance().addEnemyFire("EnemyLaser", pos.first - 4.15f, pos.second - 0.03f);
    EventQueue::getInstance().addEnemyFire("IceMeteor", 8.0f, 1.80f);
    EventQueue::getInstance().addEnemyFire("IceMeteor", 10.0f, 1.80f);
    EventQueue::getInstance().addEnemyFire("IceMeteor", 12.0f, -1.80f);
    EventQueue::getInstance().addEnemyFire("IceMeteor", 14.0f, -1.80f);
  }
  else if((shootingTime % 30) == 0){
    auto pos = getPosition();
    EventQueue::getInstance().addEnemyFire("BlueEnemyBullet", pos.first - 0.15f, pos.second - 0.03f);
  }

  shootingTime -= 1;
}

void CrystalBoss::move(){
  if(standStill > 0){
    standStill -= 1;
  }
  else{
    float tick      = 1.0f/60.0f;
    float distanceY = tick * getSpeed();
    float distanceX = 0;
    auto pos        = this->getPosition();
    if(!moveUpward) distanceY = -distanceY;
    if(pos.first + getHalfWidth() > 4.0f) distanceX = tick * getSpeed();
    setPosition(pos.first - distanceX, pos.second + distanceY);

    //If the Boss reached the highest point of flight
    if(getPosition().second  + getHalfWidth() >= 2.70f) moveUpward = false;
    //If the Boss reached the lowest point of flight
    else if(getPosition().second - getHalfWidth() <= -2.70f ) moveUpward = true;
  }
}

}
