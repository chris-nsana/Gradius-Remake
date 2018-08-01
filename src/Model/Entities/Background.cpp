#include "Background.h"

namespace Model{


Background::Background(float x, float y, float health, float damage, float speed, float width, float height, string texture)
  //The damage of the background entity absolutely has to be 0, since it spans over the whole field, but shouldn't
  //damage other entities.
 : Neutral(x, y, health, 0, speed, width, height, texture){}

Background::~Background(){}

void Background::update(){
  //A background doesn't do anything but move on every game tick.
  move();
};

void Background::move(){
  //Speed is expressed in distance per second and move is called 60 times per second
  //So move 1/60 of the speed on every call.
  float fraction   = 1.0f/60.0f;
  auto current_pos = this->getPosition();
  //The object is out of sight, wrap around to the right to simulate
  //an endless background
  if(current_pos.first < -8.0f){
    //15.960 is the position to wrap around to perfectly connect to the rightmost Background entity.
    this->setPosition(15.960f, current_pos.second);
  }
  else{
    float x_distance = fraction * this->getSpeed();
    float new_X      = current_pos.first - x_distance;
    this->setPosition(new_X, current_pos.second);
  }
};

}
