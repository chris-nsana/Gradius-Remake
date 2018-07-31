#include "Model.h"
#include "EntityFactory.h"
#include "EventQueue.h"
#include "Entities/Player.h"
#include "Entities/PlayerBullet.h"

#include <iostream>
#include <fstream>
#include <math.h>

namespace Model{

Model::Model(std::string entitiesFile, std::vector<std::string> levels, int level, bool co_op)
 : levels(levels), currentLevel(level), co_op(co_op), player1ID(0), player2ID(0), levelTime(0){

	factory = std::make_unique<EntityFactory>(entitiesFile);
}

Model::~Model(){}

void Model::createEntity(std::string type, float x, float y){
  auto entity    = factory->create(type);
  entity->setPosition(x, y);
  entities.push_back(std::move(entity));
}

void Model::startLevel(){
	nlohmann::json level;
	std::string filepath = "./../resources/levels/" + levels[currentLevel-1];
	std::ifstream file(filepath);
	file >> level;
	std::string background = level["Background"];
	std::string border     = level["Border"];
	float xpos = 0;
	for(int i = 0; i < 3; i += 1){
		//Create Background and upper+lower Border elements
    createEntity(background, xpos, 0.0f);
    createEntity(border, xpos, 2.85f);
    createEntity(border, xpos, -2.85f);
		xpos += 7.99; //7.99 instead of 8.0 to allow a tiny smidgen of overlap.
	}

	auto player1    = factory->create("Player1");
	player1->setPosition(-1.0f, 0.0f);
	this->player1ID  = player1->getID();
	entities.push_back(std::move(player1));

	std::vector<nlohmann::json> elements = level["Elements"];
	this->levelElements = std::move(elements);
}

void Model::readLevel(){
	for(auto it = elementPtr; it != levelElements.end(); ++it){
		//If it's time to process this element
		if(levelTime == (*it)["timeframe"]){
			std::string type = (*it)["entity_type"];
			float x          = (*it)["posX"];
			float y          = (*it)["posY"];
      createEntity(type, x, y);
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

void Model::update(){
	readLevel();
	for(const auto& e : entities){
		e->update();
	}
  processEvents();
  checkCollision();
	massNotify();
}

void Model::tick(){
	this->levelTime += 1;
}

void Model::massNotify(){
	//Every entity needs to notify the observer
	for(auto& e : entities){
		e->notify();
	}
}

void Model::processEvents(){
  while(!(EventQueue::getInstance().isEmpty())){
    std::unique_ptr<Event> e = std::move(EventQueue::getInstance().dequeue());
    e->execute();
  }
}

void Model::checkCollision(){
  for(auto& e1 : entities){
    for(auto&e2 : entities){
      bool horizontal = fabs((e1->getPosition().first - e2->getPosition().first)) < (e1->getHalfWidth() + e2->getHalfWidth());
      bool vertical   = fabs((e1->getPosition().second - e2->getPosition().second)) < (e1->getHalfHeight() + e2->getHalfHeight());
      //If entities intersect horizantally and vertically, we have a collision.
      if(horizontal and vertical){
        //Technically entities are colliding with themselves, but we want to ignore this case.
        if(e1->getID() == e2->getID()) continue;
        //Let the underlying entities do whatever needs to happen on collision.
        e1->onCollisionReact(*(e2.get()));
      }
    }
  }
}

void Model::destroyEntity(int ID){}

Player& Model::getPlayer1(){
	auto p1 = locateEntity(player1ID);
	Entity& entityRef = *((*p1).get());
	Player& playerRef = dynamic_cast<Player&>(entityRef);
	return playerRef;
}

Player& Model::getPlayer2(){
	auto p2 = locateEntity(player2ID);
	Entity& entityRef = *((*p2).get());
	Player& playerRef = dynamic_cast<Player&>(entityRef);
	return playerRef;
}

Model::entity_it Model::locateEntity(int eID){
	for(auto it = entities.begin(); it != entities.end(); ++it){
		if((*it)->getID() == eID) return it;
	}
	//Throw exception if not found.
}

}
