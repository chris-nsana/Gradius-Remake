#include "Neutral.h"
#include "Friendly.h"
#include "Enemy.h"

namespace Model{

Neutral::Neutral(){}

Neutral::Neutral(float x, float y, float health, float damage, float width, float height) :
		Entity(x, y, health, damage, width, height, type){}

Neutral::~Neutral(){}

bool Neutral::isNeutral() const {
	return true;
}

bool Neutral::isFriendly() const {
	return false;
}

bool Neutral::isEnemy() const {
	return false;
}


void Neutral::onCollisionReact(std::shared_ptr<Entity> otherEntity){
	//Neutral on neutral collision has no significant effect.
	return void();
}
/*
void Neutral::onCollisionReact(Friendly& other){
	//The friendly entity takes damage, but the neutral entity stays unchanged.
	float myDamage = this->getDamage();
	other.takeDamage(myDamage);
}

void Neutral::onCollisionReact(Enemy& other){
	//The Enemey entity is obstructed by this neutral entity
	other.setBlocked();

}*/
}
