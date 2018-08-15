#include "EnemyLaser.h"
#include "Model/EventQueue.h"
#include <limits>

namespace Model{

EnemyLaser::EnemyLaser(float x, float y, float health, float damage, float speed, float width, float height, string texture)
 : Enemy(x, y, std::numeric_limits<double>::infinity(), damage, speed, width, height, texture), lifeTime(10){}

 EnemyLaser::~EnemyLaser(){}

void EnemyLaser::update(){
  if(lifeTime == 0){
    EventQueue::getInstance().addEnemyDeath(getID());
  }
  else{
    lifeTime -= 1;
  }
}

void EnemyLaser::move(){}

}
