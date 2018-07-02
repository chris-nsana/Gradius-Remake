#include "Enemy.h"

namespace Model{

Enemy::Enemy(){}

Enemy::Enemy(float x, float y, float health, float damage, float width, float height, int type) :
		Entity(x, y, health, damage, width, height, type){}

Enemy::~Enemy(){}

bool Enemy::isNeutral() const {
	return false;
}

void Enemy::onCollisionReact(Neutral& other){
	//Enemy on Neutral collision leads to solid collision without damaged
	this->setBlocked()
	this->takeDamage(damage);
}

void Enemy::onCollisionReact(Friendly& other){
	thisDamage  = this->getDamage();
	otherDamage = other.getDamage();
	this->takeDamage(otherDamage);
	other.takeDamage(thisDamage);

}

void Enemy::onCollisionReact(Enemy& other){
	//Enemy on Enemy collision is bypassed by letting these entities "phase" through eachother.
	return void()
}


}
