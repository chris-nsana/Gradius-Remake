#include "Player.h"

namespace Model{

Player::Player(float x, float y, float health, float speed, float damage, float width, float height, string texture)
 : Friendly(x, y, health, damage, speed, width, height, texture){}

Player::~Player(){}

void Player::update(){}

void Player::move(){}

void Player::fire(){}

}
