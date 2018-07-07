#include "EntityFactory.h"
#include "Entities/Player.h"
#include "Entities/PlayerBullet.h"
#include "Entities/Border.h"
#include "Entities/Background.h"

namespace Model{

EntityFactory::EntityFactory(){
  nlohmann::json entities;
  std::ifstream file("./../resources/entities.json");
  file >> entities;
  this->entitiesJson = entities;
  //create the map now....
  creationMap["PlayerShip"]    = &createPlayerShip
  creationMap["PlayerBullet"]  = &createPlayerBullet
  creationMap["Border"]        = &createBorder
  creationMap["Background"]    = &createBackground

}

std::shared_ptr<Entity> EntityFactory::create(std::string entity_type){
  auto obj = entitiesJson[entity_type];
  eType = obj["entity_type"];
  creationArgs args = {obj["health"], obj["speed"], obj["damage"], obj["width"],
  obj["height"], obj["texture"], obj[]};
  ctor = creationMap[eType];
  return (*this).(*ctor)(args);

}

std::shared_ptr<Entity> EntityFactory::createPlayerShip(creationArgs& args){
  std::shared_ptr<Entity> ent_ptr = std::make_shared<Player>(args.x, args.y, args.health, args.damage,
  args.width, args.height, args.type);
  return ent_ptr;
}

std::shared_ptr<Entity> EntityFactory::createPlayerBullet(creationArgs& args){
  std::shared_ptr<Entity> ent_ptr = std::make_shared<PlayeBulletr>(args.x, args.y, args.health, args.damage,
  args.width, args.height, args.type);
  return ent_ptr;
}

std::shared_ptr<Entity> EntityFactory::createBorder(creationArgs& args){
  std::shared_ptr<Entity> ent_ptr = std::make_shared<Border>(args.x, args.y, args.health, args.damage,
  args.width, args.height, args.type);
  return ent_ptr;
}

std::shared_ptr<Entity> EntityFactory::createBackground(creationArgs& args){
  std::shared_ptr<Entity> ent_ptr = std::make_shared<Background>(args.x, args.y, args.health, args.damage,
  args.width, args.height, args.type);
  return ent_ptr;
}

}
