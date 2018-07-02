#include "Friendly.h"

namespace Model{

Friendly::Friendly(){}

Friendly::Friendly(float x, float y, float health, float damage, float width, float height, int type) :
		Entity(x, y, health, damage, width, height, type){}

Friendly::~Friendly(){}

bool Friendly::isNeutral() const {
	return false;
}

void Friendly::onCollisionReact(Neutral& other){
	//Friendly on Neutral collision has no significant effects for the other but damage for itself.
	damage = other.getDamage();
	this->takeDamage(damage);
}

void Friendly::onCollisionReact(Friendly& other){
	//Friendly on friendly collision is bypassed by letting these entities "phase" through eachother.
	damage = this->getDamage();
	other.takeDamage(damage);
}

void Friendly::onCollisionReact(Enemy& other){
	thisDamage  = this->getDamage();
	otherDamage = other.getDamage();
	this->takeDamage(otherDamage);
	other.takeDamage(thisDamage);

}

}
