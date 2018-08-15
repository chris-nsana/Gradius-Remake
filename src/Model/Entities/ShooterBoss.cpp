#include "ShooterBoss.h"
#include "Model/EventQueue.h"
#include <algorithm>

namespace Model{

ShooterBoss::ShooterBoss(float x, float y, float health, float damage, float speed, float width, float height, string texture)
 : Enemy(x, y, health, damage, speed, width, height, texture), moveUpward(true), spawnTime(180), shootingTime(15){}

 ShooterBoss::~ShooterBoss(){}

void ShooterBoss::update(){
  move();
  if(spawnTime == 0){
    spawnTime = 180;
    //Create Shooter enemies and meteors to aid the boss.
    float yCoord = getPosition().second;
    EventQueue::getInstance().addEnemyFire("EnemyShooter", 5.5f, std::min(yCoord + 1.50f, 2.0f));
    EventQueue::getInstance().addEnemyFire("EnemyShooter", 5.5f, std::max(yCoord - 1.50f, -2.0f));
    EventQueue::getInstance().addEnemyFire("RockMeteor", 5.0f, yCoord);
  }
  else{
    spawnTime -= 1;
  }

  if(shootingTime == 0){
    shootingTime = 15;
    auto pos     = getPosition();
    EventQueue::getInstance().addEnemyFire("BlueEnemyBullet", pos.first, pos.second);
  }
  else{
    shootingTime -= 1;

  }
}

void ShooterBoss::move(){
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
