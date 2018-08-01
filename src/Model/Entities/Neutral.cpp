#include "Neutral.h"
#include "Friendly.h"
#include "Enemy.h"

namespace Model{

Neutral::Neutral(){}

Neutral::Neutral(float x, float y, float health, float damage, float speed, float width, float height, string texture):
		Entity(x, y, health, damage, speed, width, height, texture){}

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

void Neutral::fire(){
	return void();
}


void Neutral::onCollisionReact(Entity& other){
	//Neutral on neutral collision has no significant effect.
	if(other.isNeutral()){
		return void();
	}

	//Neutral on friendly, the friendly object needs to take damage in this collision.
	else if(other.isFriendly()){
		other.takeDamage(getDamage(), false);
	}

	else if(other.isEnemy()){
		return void();
	}
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
