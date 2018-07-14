#include "Entity.h"

namespace Model{

Entity::Entity(){}

Entity::Entity(float x, float y, float h1, float d,float w, float h2, string tx) :
		position(x, y), health(h1), damage(d), width(w), height(h2), texture(tx)
{
	Entity::entityCount += 1;
	eID = Entity::entityCount;
	this->notifyCreation();

}

Entity::~Entity(){}


void Entity::Attach(const std::shared_ptr<View::View>& obs){
	observer = obs;
}

void Entity::Detach(){
	observer = nullptr;
}

bool Entity::isAttached() const{
	return (observer != nullptr);
}

void Entity::notifyCreation() const{
	if(isAttached()){
		observer->informCreation(getID(), getWidth(), getHeight(), getTexture());
	}
	else throw std::runtime_error("This should be a custom exception.");
}

void Entity::notify() const{
	if(isAttached()){
		observer->inform(getID(), getPosition().first, getPosition().second);
	}
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

std::string Entity::getTexture() const{
	return this->texture;
}

std::pair<float, float> Entity::getPosition() const{
	return this->position;
}

float Entity::getHealth() const{
	return this->health;
}

float Entity::getDamage() const{
	return this->damage;
}

float Entity::getWidth() const{
	return this->width;
}

float Entity::getHeight() const{
	return this->height;
}

float Entity::getHalfWidth() const{
	return (this->width / 2.0f);
}

float Entity::getHalfHeight() const{
	return (this->height / 2.0f);
}

void Entity::takeDamage(float amount){
	this->health -= amount;
}

bool Entity::isDead() const{
	return (this->health <= 0);
}

void Entity::update(){}

void Entity::move(){}

void Entity::fire(){}

bool Entity::isNeutral() const{}

bool Entity::isFriendly() const{}

bool Entity::isEnemy() const{}

void Entity::onCollisionReact(const std::unique_ptr<Entity>& otherEntity){}

int Entity::entityCount = 0;

std::shared_ptr<View::View> Entity::observer = nullptr;

}
