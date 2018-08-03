#include "Model.h"
#include "EventQueue.h"
#include "Entities/Player.h"
#include "Entities/PlayerBullet.h"

#include <iostream>
#include <fstream>
#include <math.h>

namespace Model{

Model::Model(std::string entitiesFile, std::vector<std::string> levels, int level, int lives, bool co_op)
 : factory(entitiesFile), levels(levels), currentLevel(level), co_op(co_op),
  p1(0, lives, 0, true), p2(0, lives, 0, false), levelTime(0), active(false){}


Model::~Model(){}

bool Model::isActive(){
  return active;
}

void Model::createEntity(std::string type, float x, float y){
  auto entity    = factory.create(type);
  entity->setPosition(x, y);
  entities.push_back(std::move(entity));
}

void Model::createWorldElements(nlohmann::json& levelInfo){
  std::string background = levelInfo["Background"];
  std::string border     = levelInfo["Border"];
  float xpos = 0;
  for(int i = 0; i < 3; i += 1){
    //Create Background and upper+lower Border elements
    createEntity(background, xpos, 0.0f);
    createEntity(border, xpos, 2.85f);
    createEntity(border, xpos, -2.85f);
    xpos += 7.99; //7.99 instead of 8.0 to allow a tiny smidgen of overlap.
  }

  auto player1    = factory.create("Player1");
  player1->setPosition(-1.0f, 0.0f);
  this->p1.setID(player1->getID());
  entities.push_back(std::move(player1));

  if(co_op){
    //Create player2
  }
}

void Model::startLevel(){
  nlohmann::json level;
  std::string filepath = "./../resources/levels/" + levels[currentLevel-1];
  std::ifstream file(filepath);
  file >> level;
  createWorldElements(level);
  std::vector<nlohmann::json> elements = level["Elements"];
  this->levelElements = std::move(elements);
  this->elementPtr    = this->levelElements.begin();
  this->active        = true; //When a level starts the game is active.
}

void Model::resetLevel(){
  bool endGame = false;
  if(p1.getLives() == 0){
    //The only player has no lives left, so the game isn't active anymore.
    if(!co_op) endGame = true;
    //Or both player1 and player2 have no lives left.
    else if(co_op and (p2.getLives()==0)) endGame = true;
  }
  //No point in rebuilding the world if no players are alive, exit the method.
  if(endGame){
    this->active= false;
    return void();
  }
  //Recreate the world a little bit before one of the players died.
  nlohmann::json level;
  std::string filepath = "./../resources/levels/" + levels[currentLevel-1];
  std::ifstream file(filepath);
  file >> level;
  //Clear the whole game world
  this->entities.clear();
  //Recreate the bare bones
  createWorldElements(level);
  //Take a step back in the level advancement
  if(elementPtr != levelElements.begin()){
    --elementPtr;
    //To make sure that next of readLevel reads the elements before death.
    this->levelTime = ((*elementPtr)["time"]);
  }
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
  //If the Model is frozen, we do not update anything and just wait.
  if(isFrozen()){
    wait();
    return void();
  }

  readLevel();
  for(const auto& e : entities){
    e->update();
  }
  checkCollision();
  processEvents();
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
    //If the entity is dead and waiting to be deleted out of the Model, we ignore it.
    if(e1->isDead()) continue;
    for(auto&e2 : entities){
      //If the entity is dead and waiting to be deleted out of the Model, we ignore it.
      if(e2->isDead()) continue;
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

void Model::destroyEntity(int ID){
  auto position = locateEntity(ID);
  entities.erase(position);
}

void Model::decreasePlayerLives(int id, int lives){
  if(p1.getID() == id){
    p1.takeLives(lives);
  }
  else if(p2.getID() == id){
    p2.takeLives(lives);
  }
  else{
    //throw exception here
  }
}

Player& Model::getPlayer1(){
    auto player1 = locateEntity(this->p1.getID());
    Entity& entityRef = *((*player1).get());
    Player& playerRef = dynamic_cast<Player&>(entityRef);
    return playerRef;
}

Player& Model::getPlayer2(){
    auto player2 = locateEntity(this->p2.getID());
    Entity& entityRef = *((*player2).get());
    Player& playerRef = dynamic_cast<Player&>(entityRef);
    return playerRef;
}

void Model::freeze(double time){
  waitingTime = time;
}

void Model::wait(){
  waitingTime -= (1.0/60.0f);
}

void Model::unfreeze(){
  waitingTime = 0.0f;
}

bool Model::isFrozen() const{
  return (waitingTime >= 0.0f);
}

Model::entity_it Model::locateEntity(int eID){
    for(auto it = entities.begin(); it != entities.end(); ++it){
        if((*it)->getID() == eID) return it;
    }
    //Throw exception if not found.
    throw std::out_of_range("No");
}

}
