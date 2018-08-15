#include "Enemy.h"
#include "Model/EventQueue.h"

namespace Model{

Enemy::Enemy(){}

Enemy::Enemy(float x, float y, float health, float damage, float speed, float width, float height, string texture) :
		Entity(x, y, health, damage, speed, width, height, texture){}

Enemy::~Enemy(){}

bool Enemy::isNeutral() const{
	return false;
}

bool Enemy::isFriendly() const{
	return false;
}

bool Enemy::isEnemy() const{
	return true;
}

void Enemy::takeDamage(float amount, bool enemy){
	//Let the base class handle the subtraction of life
	Entity::takeDamage(amount, enemy);
	//If the Enemy entity died we store that event
	if(this->isDead()){
		int id = getID();
		EventQueue::getInstance().addEnemyDeath(id);
	}
	//Else the Enemy took damage and survived, inform the View about the taken damage
	//to visually represent it by fading the sprite.
	else if(auto spt = observer.lock()){
		spt->informHit(getID());
	}
	else throw std::runtime_error("An entity tried to notify its changes to the observer, but no observer was attached to it!");
}

void Enemy::onCollisionReact(Entity& other){
	Entity& thisEntity = *this;
	//Collision with Friendly object, take damage and deal damage
	if(other.isFriendly()){
		float otherDamage = other.getDamage();
		float thisDamage  = thisEntity.getDamage();
		other.takeDamage(thisDamage, false);
		thisEntity.takeDamage(otherDamage, true);
		if(this->isDead()) EventQueue::getInstance().addPointsGain(other.getCreatorID(), thisEntity.getWorth());
	}

	//Collision with Neutral element, take damage
	else if(other.isNeutral()){
		//We'll implement pushBack() later
	}

	//Collision with Enemy, do nothing and phase through eachother
	else if(other.isEnemy()) return void();
}


}
