#include "Entity.h"
Entity::Entity() : position(0,0){};

Entity::Entity(float x, float y, float r, int eType) : position(x, y), radius(r), type(eType){
	entityCount += 1;
	eID = entityCount;

};

Entity::~Entity(){};


void Entity::Attach(const std::shared_ptr<View::View>& obs){
	observer = obs;
}

void Entity::Detach(){
	observer = nullptr;
}

bool Entity::isAttached() const{
	return (observer != nullptr);
}

void Entity::notify() const{
if(isAttached())observer->inform(getPosition().first, getPosition().second, getID(), getType());

else throw std::runtime_error("An entity tried to notify its observer, but no observer was attached to it!");
}

void Entity::notifyDeath() const{
if(isAttached())observer->deleteEntity(getID());

else throw std::runtime_error("An entity tried to notify its observer, but no observer was attached to it!");
}

void Entity::setPosition(float x, float y){
	position.first  = x;
	position.second = y;
}

int Entity::getID() const{
	return eID;
}

int Entity::getType() const{
	return type;
}


std::pair<float, float> Entity::getPosition() const{
	return this->position;
}

float Entity::getRadius() const{
	return this->radius;
}
int Entity::entityCount = 0;

std::shared_ptr<View::View> Entity::observer = nullptr;
