#include "World.h"
#include "Background.h"
#include "Border.h"
#include "GameGlobals.h"
#include <iostream>
World::World() : Entity(0.0f, 0.0f, 0.0f, 2){}

World::~World(){}

void World::update(){
	float newX;
	//Wrap around the background if 600 ticks (roughly 10 seconds) has past.
	if(worldElements[0]->getPosition().first < -7.90f){
		staticPtr& bground = worldElements[0];
		bground->setPosition(bground->getPosition().first + 16.0f, bground->getPosition().second);
		staticPtr& top = worldElements[2];
		top->setPosition(top->getPosition().first + 16.0f, top->getPosition().second);
		staticPtr& bottom = worldElements[4];
		bottom->setPosition(bottom->getPosition().first + 16.0f, bottom->getPosition().second);
	}
	else if(worldElements[1]->getPosition().first < -7.90f){
		staticPtr& bground = worldElements[1];
		bground->setPosition(bground->getPosition().first + 16.0f, bground->getPosition().second);
		staticPtr& top = worldElements[3];
		top->setPosition(top->getPosition().first + 16.0f, top->getPosition().second);
		staticPtr& bottom = worldElements[5];
		bottom->setPosition(bottom->getPosition().first + 16.0f, bottom->getPosition().second);

	}
	for(auto& e : worldElements){
		newX = e->getPosition().first - 0.01333333333f;
		e->setPosition(newX, e->getPosition().second);
	}
}

void World::setWorld(){
	//The creations happen in pairs to emulate a sidescrolling effect.
	//Creation of the background.
	createWorldElement(0, 0, 3);
	createWorldElement(8, 0, 3);
	createWorldElement(0, 2.80, 4);
	createWorldElement(8, 2.80, 4);
	createWorldElement(0, -2.80, 4);
	createWorldElement(8, -2.80, 4);
}

void World::createWorldElement(float x, float y, int type){

	switch(type){
	case 3:
		worldElements.push_back(std::unique_ptr<Entity>(new Background(x, y)));
		break;

	case 4:
		worldElements.push_back(std::unique_ptr<Entity>(new Border(x, y)));
		break;


	default:
		std::cout << type << std::endl;
		//throw std::invalid_argument("Error! Attempted to make an WorldElement but there is no such type of WorldElement");
		break;
	}

}

void World::notify() const{
	for(auto& e : worldElements){
		e->notify();
	}
}
