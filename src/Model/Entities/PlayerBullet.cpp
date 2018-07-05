#include "PlayerBullet.h"

namespace Model{

PlayerBullet::PlayerBullet(float x, float y, float health, float damage, float width, float height)
 : Friendly(x, y, health, damage, width, height){}

PlayerBullet::~PlayerBullet(){}

void PlayerBullet::move(){
	std::pair<float, float> pos = this->getPosition();
	setPosition(pos.first + 0.075f, pos.second);
}

}
