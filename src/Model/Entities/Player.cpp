#include "Player.h"

namespace Model{

Player::Player(float x, float y, float health, float damage, float width, float height) 
 : Friendly(x, y, health, damage, width, height){}

Player::~Player(){}


void Player::move(){}

}
