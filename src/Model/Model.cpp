#include "Model.h"
#include "EntityFactory.h"
#include "Entities/Player.h"
#include "Entities/PlayerBullet.h"
#include <iostream>

namespace Model{

Model::Model(std::string entitiesFile, bool co_op) : player1ID(0), player2ID(0){
	factory         = std::make_unique<EntityFactory>(entitiesFile);
	auto player1    = factory->create("Player1");
	player1->setPosition(0.0f, 0.0f);
	this->player1ID  = player1->getID();
	entities.push_back(std::move(player1));

	if (co_op){
		auto player2      = factory->create("Player2");
		this-> player2ID  = player2->getID();
		entities.push_back(std::move(player2));
	}
}

Model::~Model(){}

void Model::createEntity(float x, float y, int type, bool dynamic){
//Obsolete
}

void Model::setLevel(){
	//Different implementaton
}

std::unique_ptr<Entity>& Model::locateEntity(int eID){
	//Still to implement.
}

void Model::movePlayer(float x, float y){
	/***
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
	player->setPosition(newX, newY);*/
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
	//Every entity needs to notify the observer
	for(auto& e : entities){
		e->notify();
	}
}

void Model::playerFire(){
	//
	//createEntity(player->getPosition().first + 0.2f, player->getPosition().second - 0.075f, 1, true);
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
