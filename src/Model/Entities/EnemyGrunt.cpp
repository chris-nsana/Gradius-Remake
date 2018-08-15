#include "EnemyGrunt.h"
#include "Model/EventQueue.h"

namespace Model{

EnemyGrunt::EnemyGrunt(float x, float y, float health, float damage, float speed, float width, float height, string texture)
 : Enemy(x, y, health, damage, speed, width, height, texture){}

 EnemyGrunt::~EnemyGrunt(){}


void EnemyGrunt::takeDamage(float amount, bool enemy){
  //Let the base method handle the amount of damage taken
  Enemy::takeDamage(amount, enemy);
  if(this->isDead()){
    //If this entity dies, tell its brethren to swarm to this location.
    swarmPoint = getPosition();

  }
}

void EnemyGrunt::update(){
  move();
}

void EnemyGrunt::move(){
  float tick      = 1.0f/60.0f;
  float distanceX = tick * getSpeed();
  float distanceY = 0.0f;
  auto pos        = this->getPosition();
  if(swarmPoint.first < pos.first){
    //distanceX = 0.5 * distanceX;
    if(pos.second > swarmPoint.second){
      distanceY = -0.1 * (tick * getSpeed());
    }
    else if(pos.second < swarmPoint.second){
      distanceY = + 0.35 *(tick * getSpeed());
    }
  }
  setPosition(pos.first - distanceX, pos.second + distanceY);
  //Destroy entity that leaves the playable and visible part of the world.
  if(getPosition().first < (-4.0f - getHalfWidth())){
    EventQueue::getInstance().addEnemyDeath(getID());
  }
}

std::pair<float, float> EnemyGrunt::swarmPoint = {std::numeric_limits<double>::infinity(), 0};

}
