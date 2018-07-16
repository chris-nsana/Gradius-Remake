#include "Model.h"
#include "EntityFactory.h"
#include "Entities/Player.h"
#include "Entities/PlayerBullet.h"

#include <iostream>
#include <fstream>

namespace Model{

Model::Model(std::string entitiesFile, bool co_op) : player1ID(0), player2ID(0){
	factory         = std::make_unique<EntityFactory>(entitiesFile);
	this->levels = {"level1.json", "level2.json", "level3.json"};

	if (co_op){
		auto player2      = factory->create("Player2");
		player2->setPosition(2.0f, 0.0f);
		this-> player2ID  = player2->getID();
		entities.push_back(std::move(player2));
	}
}

Model::~Model(){}

void Model::createEntity(float x, float y, int type, bool dynamic){
//Obsolete
}

void Model::startLevel(){
	nlohmann::json level;
	std::string filepath = "./../resources/levels/" + levels[currentLevel-1];
	std::ifstream file(filepath);
	file >> level;
	std::string background = level["Background"];
	std::cout<< "powerful creation" << std::endl;
	std::string border     = level["Border"];
	float xpos = 0;
	for(int i = 0; i < 3; i += 1){
		//Create Background and Border elements
		auto bground      = factory->create(background);
		auto upper_border = factory->create(border);
		auto lower_border = factory->create(border);
		bground->setPosition(xpos, 0.0f);
		upper_border->setPosition(xpos,  2.85f);
		lower_border->setPosition(xpos, -2.85f);
		entities.push_back(std::move(bground));
		entities.push_back(std::move(upper_border));
		entities.push_back(std::move(lower_border));
		xpos += 4;
	}

	auto player1    = factory->create("Player1");
	player1->setPosition(0.0f, 0.0f);
	this->player1ID  = player1->getID();
	entities.push_back(std::move(player1));
	
	std::vector<nlohmann::json> elements = level["Elements"];
	this->levelElements = std::move(elements);
}

std::unique_ptr<Entity>& Model::locateEntity(int eID){
	//Still to implement.
}

void Model::readLevel(){
	for(auto it = elementPtr; it != levelElements.end(); ++it){
		//If it's time to process this element
		if(levelTime == (*it)["timeframe"]){
			std::string type = (*it)["entity_type"];
			float x          = (*it)["posX"];
			float y          = (*it)["posY"];
			auto new_entity = factory->create(type);
			new_entity->setPosition(x, y);
			entities.push_back(std::move(new_entity));
		}
		//Else it's too early and we wait. All events after this one also have to wait so we break out of the method.
		else{
			//Store this location in the vector to resume at later ticks.
			elementPtr = it;
			return void();
		}
	}
	//If all elements are already read
	elementPtr = levelElements.end();
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
	readLevel();
	for(const auto& e : entities){
		e->update();
	}
	massNotify();
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
