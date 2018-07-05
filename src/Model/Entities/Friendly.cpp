#include "Friendly.h"
#include "Neutral.h"
#include "Enemy.h"

namespace Model{

Friendly::Friendly(){}

Friendly::Friendly(float x, float y, float health, float damage, float width, float height) :
		Entity(x, y, health, damage, width, height, type){}

Friendly::~Friendly(){}

bool Friendly::isNeutral() const {
	return false;
}

bool Friendly::isFriendly() const {
	return true;
}

bool Friendly::isEnemy() const {
	return false;
}

void Friendly::onCollisionReact(std::shared_ptr<Entity> otherEntity){
	//Friendly on Neutral collision has no significant effects for the other but damage for itself.
	/*float otherDamage = other.getDamage();
	this->takeDamage(otherDamage);*/
}
/*
void Friendly::onCollisionReact(Friendly& other){
	//Friendly on friendly collision is bypassed by letting these entities "phase" through eachother.
	return void();
}

void Friendly::onCollisionReact(Enemy& other){
	float thisDamage  = this->getDamage();
	float otherDamage = other.getDamage();
	this->takeDamage(otherDamage);
	other.takeDamage(thisDamage);

}*/

}
