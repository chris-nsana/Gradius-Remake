#include "Player.h"

namespace Model{

Player::Player(float x, float y, float health, float speed, float damage, float width, float height, string texture)
 : Friendly(x, y, health, damage, speed, width, height, texture){}

Player::~Player(){}

void Player::update(){}

void Player::move(){}

void Player::fire(){}

void Player::moveLeft(){
  float tick       = 1.0f / 60.0f;
  float xMovement  = tick * 0.75f * this->getSpeed();
  auto current_pos = this->getPosition();
  float newX       = current_pos.first - xMovement;
  //Check if the ship is flying out of the field from the left.
  if(newX < -3.525f) newX = -3.525f;
  this->setPosition(newX, current_pos.second);
}

void Player::moveRight(){
  float tick       = 1.0f / 60.0f;
  float xMovement  = tick * this->getSpeed();
  auto current_pos = this->getPosition();
  float newX       = current_pos.first + xMovement;
  //Check if the ship is flying out of the field from the right.
  if(newX > 3.50) newX = 3.50f;
  this->setPosition(newX, current_pos.second);
}

void Player::moveUp(){
  float tick       = 1.0f / 60.0f;
  float yMovement  = tick * 0.75f *this->getSpeed();
  auto current_pos = this->getPosition();
  float newY       = current_pos.second + yMovement;
  this->setPosition(current_pos.first, newY);
}

void Player::moveDown(){
  float tick       = 1.0f / 60.0f;
  float yMovement  = tick * 0.75f *this->getSpeed();
  auto current_pos = this->getPosition();
  float newY       = current_pos.second - yMovement;
  this->setPosition(current_pos.first, newY);
}


}
