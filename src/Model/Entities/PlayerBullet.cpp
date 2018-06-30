#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(float x, float y) : DynamicEntity(x, y, 0.1f, 1, 100), originX(x), originY(x){}

PlayerBullet::~PlayerBullet(){}

void PlayerBullet::move(){
	std::pair<float, float> pos = this->getPosition();
	setPosition(pos.first + 0.075f, pos.second);
}



