#include "EntityFactory.h"
#include "Entities/Player.h"
#include "Entities/PlayerBullet.h"
#include "Entities/Border.h"
#include "Entities/Background.h"
#include <fstream>

namespace Model{

EntityFactory::EntityFactory(std::string entitiesFile){
  nlohmann::json entities;
  std::ifstream file{entitiesFile};
  file >> entities;
  this->entitiesJson = entities;
  //create the map now....
  creationMap["PlayerShip"]    = &EntityFactory::createPlayerShip;
  creationMap["PlayerBullet"]  = &EntityFactory::createPlayerBullet;
  creationMap["Border"]        = &EntityFactory::createBorder;
  creationMap["Background"]    = &EntityFactory::createBackground;

}

EntityFactory::~EntityFactory(){}

std::unique_ptr<Entity> EntityFactory::create(std::string entity_type){
  auto obj = entitiesJson[entity_type];
  std::string eType = obj["entity_type"];
  creationArgs args = {100, 100, obj["health"], obj["speed"], obj["damage"],
  obj["width"], obj["height"], obj["texture"]};
  auto ctor = creationMap[eType];
  return (this->*ctor)(args);

}

std::unique_ptr<Entity> EntityFactory::createPlayerShip(creationArgs& args){
  std::unique_ptr<Entity> ent_ptr = std::make_unique<Player>(args.x, args.y, args.health, args.damage,
  args.width, args.height, args.texture);
  return ent_ptr;
}

std::unique_ptr<Entity> EntityFactory::createPlayerBullet(creationArgs& args){
  std::unique_ptr<Entity> ent_ptr = std::make_unique<PlayerBullet>(args.x, args.y, args.health, args.damage,
  args.width, args.height, args.texture);
  return ent_ptr;
}

std::unique_ptr<Entity> EntityFactory::createBorder(creationArgs& args){
  std::unique_ptr<Entity> ent_ptr = std::make_unique<Border>(args.x, args.y, args.health, args.damage,
  args.width, args.height, args.texture);
  return ent_ptr;
}

std::unique_ptr<Entity> EntityFactory::createBackground(creationArgs& args){
  std::unique_ptr<Entity> ent_ptr = std::make_unique<Background>(args.x, args.y, args.health, args.damage,
  args.width, args.height, args.texture);
  return ent_ptr;
}

}
