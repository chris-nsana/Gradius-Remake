#include "PlayerBullet.h"

namespace Model{

PlayerBullet::PlayerBullet(float x, float y, float health, float damage, float width, float height, string texture)
 : Friendly(x, y, health, damage, width, height, texture){}

PlayerBullet::~PlayerBullet(){}

void PlayerBullet::move(){
	std::pair<float, float> pos = this->getPosition();
	setPosition(pos.first + 0.075f, pos.second);
}

void PlayerBullet::update(){}

void PlayerBullet::fire(){}

}
