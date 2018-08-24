#include "Entity.h"
#include "Game/GameExceptions.h"

namespace Model{

Entity::Entity(){}

Entity::Entity(float x, float y, float h1, float d, float s, float w, float h2, string tx) :
		position(x, y), health(h1), damage(d), speed(s), width(w), height(h2), worth(0), creatorID(0), texture(tx)
{
	Entity::entityCount += 1;
	eID = Entity::entityCount;
	this->notifyCreation();

}

Entity::~Entity(){
	this->notifyDeath();
}


void Entity::attach(const std::shared_ptr<View::View>& obs){
	Entity::observer = obs;
}

void Entity::detach(){
	observer.reset();
}

bool Entity::isAttached() const{
	return (observer.expired());
}

void Entity::notifyCreation() const{
	if(auto spt = observer.lock()){
		spt->informCreation(getID(), getWidth(), getHeight(), getTexture());
	}
	else throw Game::ObserverError("An entity tried to notify, but no observer was attached.");
}

void Entity::notify() const{
	if(auto spt = observer.lock()){
		spt->inform(getID(), getPosition().first, getPosition().second);
	}
	else throw Game::ObserverError("An entity tried to notify, but no observer was attached.");
}

void Entity::notifyDeath() const{
	if(auto spt = observer.lock()){
		spt->informDeath(getID());
	}
	else throw Game::ObserverError("An entity tried to notify, but no observer was attached.");
	}

void Entity::setPosition(float x, float y){
	position.first  = x;
	position.second = y;
}

std::pair<float, float> Entity::getPosition() const{
	return this->position;
}

float Entity::getDamage() const{
	return this->damage;
}

float Entity::getSpeed() const{
	return this->speed;
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

float Entity::getWorth() const{
	return this->worth;
}

float Entity::getCreatorID() const{
	return this->creatorID;
}

int Entity::getID() const{
	return eID;
}

std::string Entity::getTexture() const{
	return this->texture;
}

void Entity::setWorth(int worth){
	this->worth = worth;
}

void Entity::setCreatorID(int id){
	this->creatorID = id;
}

void Entity::takeDamage(float amount, bool enemy){
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

void Entity::onCollisionReact(Entity& other){}

int Entity::entityCount = 0;

std::weak_ptr<View::View> Entity::observer = std::weak_ptr<View::View>();

}
