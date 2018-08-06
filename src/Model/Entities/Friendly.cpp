#include "Friendly.h"
#include "Neutral.h"
#include "Enemy.h"
#include "Model/EventQueue.h"

namespace Model{

Friendly::Friendly(){}

Friendly::Friendly(float x, float y, float health, float damage, float speed, float width, float height, string texture) :
		Entity(x, y, health, damage, speed, width, height, texture){}

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

void Friendly::takeDamage(float amount, bool enemy){
	//Let the base class handle the subtraction of life
	Entity::takeDamage(amount, enemy);
	//If the Friendly entity died we store that event
	if(this->isDead()){
		int id = getID();
		EventQueue::getInstance().addFriendlyDeath(id);
	}
}

void Friendly::onCollisionReact(Entity& other){
	Entity& thisEntity = *this;
	//Collision with Friendly object, do nothing a.k.a phase through eachother
	if(other.isFriendly()) return void();

	//Collision with Neutral element, take damage
	else if(other.isNeutral()){
		float otherDamage = other.getDamage();
		thisEntity.takeDamage(otherDamage, false);
	}

	//Collision with Enemy, take damage and deal damage
	else if(other.isEnemy()){
		float otherDamage = other.getDamage();
		float thisDamage  = thisEntity.getDamage();
		thisEntity.takeDamage(otherDamage, true);
		other.takeDamage(thisEntity.getDamage(), false);
		if(other.isDead()) EventQueue::getInstance().addPointsGain(thisEntity.getCreatorID(), other.getWorth());
	}
}

}
