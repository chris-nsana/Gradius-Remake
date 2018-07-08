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

std::unique_ptr<Entity> EntityFactory::create(std::string entity_type){
  auto obj = entitiesJson[entity_type];
  eType = obj["entity_type"];
  creationArgs args = {obj["health"], obj["speed"], obj["damage"], obj["width"],
  obj["height"], obj["texture"]};
  ctor = creationMap[eType];
  return (*this).(*ctor)(args);

}

std::unique_ptr<Entity> EntityFactory::createPlayerShip(creationArgs& args){
  std::unique_ptr<Entity> ent_ptr = std::make_unique<Player>(args.x, args.y, args.health, args.damage,
  args.width, args.height, args.type);
  return ent_ptr;
}

std::unique_ptr<Entity> EntityFactory::createPlayerBullet(creationArgs& args){
  std::unique_ptr<Entity> ent_ptr = std::make_unique<PlayeBulletr>(args.x, args.y, args.health, args.damage,
  args.width, args.height, args.type);
  return ent_ptr;
}

std::unique_ptr<Entity> EntityFactory::createBorder(creationArgs& args){
  std::unique_ptr<Entity> ent_ptr = std::make_unique<Border>(args.x, args.y, args.health, args.damage,
  args.width, args.height, args.type);
  return ent_ptr;
}

std::unique_ptr<Entity> EntityFactory::createBackground(creationArgs& args){
  std::unique_ptr<Entity> ent_ptr = std::make_unique<Background>(args.x, args.y, args.health, args.damage,
  args.width, args.height, args.type);
  return ent_ptr;
}

}
