#include "EntityFactory.h"
#include "Entities/Player.h"
#include "Entities/PlayerBullet.h"
#include "Entities/Border.h"
#include "Entities/Background.h"

namespace Model{

EntityFactory::EntityFactory(){
  json entities;
  std::ifstream file("./../resources/entities.json");
  file >> entities;
  this->entitiesJson = entities;
  //create the map now....
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
