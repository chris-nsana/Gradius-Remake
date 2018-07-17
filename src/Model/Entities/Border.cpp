#include "Border.h"

namespace Model{

Border::Border(float x, float y, float health, float damage, float speed, float width, float height, string texture)
 : Neutral(x, y, health, damage, speed, width, height, texture){}

Border::~Border(){};

void Border::update(){
  //A border does nothing but move on every tick.
  move();
}

void Border::move(){
  //Speed is expressed in distance per second and move is called 60 times per second
  //So move 1/60 of the speed on every call.
  float fraction   = 1.0f/60.0f;
  auto current_pos = this->getPosition();
  //The object is out of sight, wrap around to the right to simulate
  //an endless border
  if(current_pos.first < -8.0f){
    //15.960 is the position to wrap around to perfectly connect to the rightmost Border entity.
    this->setPosition(15.960, current_pos.second);
  }
  else{
    float x_distance = fraction * this->getSpeed();
    float new_X      = current_pos.first - x_distance;
    this->setPosition(new_X, current_pos.second);
  }
}

}
