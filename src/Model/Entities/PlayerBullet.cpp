#include "PlayerBullet.h"
#include "Model/EventQueue.h"

namespace Model{

PlayerBullet::PlayerBullet(float x, float y, float health, float damage, float speed, float width, float height, string texture)
 : Friendly(x, y, health, damage, speed, width, height, texture){}

PlayerBullet::~PlayerBullet(){}

void PlayerBullet::move(){
	std::pair<float, float> pos = this->getPosition();
	setPosition(pos.first + 0.075f, pos.second);
  //Destroy entity that leaves the playable and visible part of the world.
  if(getPosition().first > (4.0f + getHalfWidth())){
    EventQueue::getInstance().addFriendlyDeath(getID());
  }
}

void PlayerBullet::update(){
  move();
}

void PlayerBullet::fire(){}

void PlayerBullet::setShooterID(int id){
  this->shooterID = id;
}

int PlayerBullet::getShooterID() const{
  return shooterID;
}

}
