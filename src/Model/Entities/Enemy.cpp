#include "Enemy.h"

namespace Model{

Enemy::Enemy(){}

Enemy::Enemy(float x, float y, float health, float damage, float width, float height) :
		Entity(x, y, health, damage, width, height, type){}

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

void Enemy::onCollisionReact(std::shared_ptr<Entity> otherEntity){
	//Enemy on Neutral collision leads to solid collision without damaged
	//this->setBlocked();
}

/*
void Enemy::onCollisionReact(Friendly& other){
	float thisDamage  = this->getDamage();
	float otherDamage = other.getDamage();
	this->takeDamage(otherDamage);
	other.takeDamage(thisDamage);

}

void Enemy::onCollisionReact(Enemy& other){
	//Enemy on Enemy collision is bypassed by letting these entities "phase" through eachother.
	return void();
}*/


}
