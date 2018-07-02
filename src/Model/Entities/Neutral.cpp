#include "Neutral.h"

namespace Model{

Neutral::Neutral(){}

Neutral::Neutral(float x, float y, float health, float damage, float width, float height, int type) :
		Entity(x, y, health, damage, width, height, type){}

Neutral::~Neutral(){}

bool Neutral::isNeutral() const {
	return true;
}

void Neutral::onCollisionReact(Neutral& other){
	//Neutral on neutral collision has no significant effect.
	return void()
}

void Neutral::onCollisionReact(Friendly& other){
	//The friendly entity takes damage, but the neutral entity stays unchanged.
	damage = this->getDamage();
	other.takeDamage(damage);
}

void Neutral::onCollisionReact(Enemy& other){
	//The Enemey entity is obstructed by this neutral entity
	other.setBlocked();

}

}
