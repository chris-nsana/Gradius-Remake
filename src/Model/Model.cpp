#include "Model.h"
#include "Entities/Player.h"
#include "Entities/PlayerBullet.h"
#include <iostream>

namespace Model{

Model::Model() : player(nullptr){}

Model::~Model(){}

void Model::createEntity(float x, float y, int type, bool dynamic){
//Obsolete
}

void Model::setLevel(){
	//Different implementaton
}

void Model::movePlayer(float x, float y){
	std::pair<float, float> playerPos = player->getPosition();
	float newX = playerPos.first + x;
	float newY = playerPos.second +y;
	if(newX < -3.525f) newX = -3.525f;
	else if(newX > 3.50) newX = 3.50f;
	if(newY > 2.4000){
		newY = 2.4000;
		//do the other thing
	}
	else if(newY < -2.42500){
		newY = -2.42500;
		//do your thing
	}
	player->setPosition(newX, newY);
}

void Model::update(){
	/*
	//Update the world elements
	worldPtr->update();
	//Update the dynamic entities
	for(auto& d : dynamicEntities){
		d->move();
	}*/
}

void Model::massNotify(){
	/*
	//Of course the player has to notify the observer of its changes
	player->notify();
	//All the dynamicEntities in the model have to notify their changes as well.
	for(auto& ptr : dynamicEntities){
		ptr->notify();
	}
	//The world elements need to notify their changes as well.
	worldPtr->notify();*/
}

void Model::playerFire(){
	//
	createEntity(player->getPosition().first + 0.2f, player->getPosition().second - 0.075f, 1, true);
}

void Model::checkCollision(){
	bool collision = false;
	/*float left;
	float right;
	for(auto& ptr : dynamicEntities){
		left = (ptr->getPosition().first - arg->getPosition().first)**2 + (arg->getPosition().second + ptr->getPosition().first)**2;
		right = (ptr->getRadius() + arg->getRadius())**2;
		if(left <= right){
			collision = true;
			ptr->notifyDeath();
		}
	}
	if(collision)destroyEntity(arg);*/
	return void();
}

}
