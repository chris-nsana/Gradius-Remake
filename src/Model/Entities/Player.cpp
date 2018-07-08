#include "Player.h"

namespace Model{

Player::Player(float x, float y, float health, float damage, float width, float height, string texture)
 : Friendly(x, y, health, damage, width, height, texture){}

Player::~Player(){}

void Player::update(){}

void Player::move(){}

void Player::fire(){}

}
