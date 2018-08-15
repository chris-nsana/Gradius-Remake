#include "EntityFactory.h"
#include "Entities/Player.h"
#include "Entities/PlayerBullet.h"
#include "Entities/Border.h"
#include "Entities/Background.h"
#include "Entities/EnemyBullet.h"
#include "Entities/EnemyLaser.h"
#include "Entities/EnemyGrunt.h"
#include "Entities/FlyingSaucer.h"
#include "Entities/FlyingObstacle.h"
#include "Entities/EnemyShooter.h"
#include "Entities/SaucerBoss.h"
#include "Entities/ShooterBoss.h"
#include "Entities/CrystalBoss.h"
#include <fstream>

namespace Model{

EntityFactory::EntityFactory(std::string entitiesFile){
  nlohmann::json entities;
  std::ifstream file{entitiesFile};
  file >> entities;
  this->entitiesJson = entities;
  //Create the map now....
  creationMap["PlayerShip"]         = &EntityFactory::createPlayerShip;
  creationMap["PlayerBullet"]       = &EntityFactory::createPlayerBullet;
  creationMap["Border"]             = &EntityFactory::createBorder;
  creationMap["Background"]         = &EntityFactory::createBackground;
  creationMap["EnemyBullet"]        = &EntityFactory::createEnemyBullet;
  creationMap["EnemyLaser"]         = &EntityFactory::createEnemyLaser;
  creationMap["EnemyGrunt"]         = &EntityFactory::createEnemyGrunt;
  creationMap["FlyingSaucer"]       = &EntityFactory::createFlyingSaucer;
  creationMap["FlyingObstacle"]     = &EntityFactory::createFlyingObstacle;
  creationMap["EnemyShooter"]       = &EntityFactory::createEnemyShooter;
  creationMap["SaucerBoss"]         = &EntityFactory::createSaucerBoss;
  creationMap["ShooterBoss"]        = &EntityFactory::createShooterBoss;
  creationMap["CrystalBoss"]        = &EntityFactory::createCrystalBoss;

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
  std::unique_ptr<Entity> ent_ptr = std::make_unique<Player>(args.x, args.y, args.health, args.speed,
  args.damage, args.width, args.height, args.texture);
  return ent_ptr;
}

std::unique_ptr<Entity> EntityFactory::createPlayerBullet(creationArgs& args){
  std::unique_ptr<Entity> ent_ptr = std::make_unique<PlayerBullet>(args.x, args.y, args.health, args.damage,
  args.speed, args.width, args.height, args.texture);
  return ent_ptr;
}

std::unique_ptr<Entity> EntityFactory::createBorder(creationArgs& args){
  std::unique_ptr<Entity> ent_ptr = std::make_unique<Border>(args.x, args.y, args.health, args.damage,
  args.speed, args.width, args.height, args.texture);
  return ent_ptr;
}

std::unique_ptr<Entity> EntityFactory::createBackground(creationArgs& args){
  std::unique_ptr<Entity> ent_ptr = std::make_unique<Background>(args.x, args.y, args.health, args.damage,
  args.speed, args.width, args.height, args.texture);
  return ent_ptr;
}

std::unique_ptr<Entity> EntityFactory::createEnemyBullet(creationArgs& args){
  std::unique_ptr<Entity> ent_ptr = std::make_unique<EnemyBullet>(args.x, args.y, args.health, args.damage,
  args.speed, args.width, args.height, args.texture);
  //Enemy bullets have no worth
  ent_ptr->setWorth(0);
  return ent_ptr;
}

std::unique_ptr<Entity> EntityFactory::createEnemyLaser(creationArgs& args){
  std::unique_ptr<Entity> ent_ptr = std::make_unique<EnemyLaser>(args.x, args.y, args.health, args.damage,
  args.speed, args.width, args.height, args.texture);
  //EnemyLasers have no worth
  ent_ptr->setWorth(0);
  return ent_ptr;
}

std::unique_ptr<Entity> EntityFactory::createEnemyGrunt(creationArgs& args){
  std::unique_ptr<Entity> ent_ptr = std::make_unique<EnemyGrunt>(args.x, args.y, args.health, args.damage,
  args.speed, args.width, args.height, args.texture);
  int worth = entitiesJson["EnemyGrunt"]["worth"];
  ent_ptr->setWorth(worth);
  return ent_ptr;
}

std::unique_ptr<Entity> EntityFactory::createFlyingSaucer(creationArgs& args){
  std::unique_ptr<Entity> ent_ptr = std::make_unique<FlyingSaucer>(args.x, args.y, args.health, args.damage,
  args.speed, args.width, args.height, args.texture);
  int worth = entitiesJson["FlyingSaucer"]["worth"];
  ent_ptr->setWorth(worth);
  return ent_ptr;
}
std::unique_ptr<Entity> EntityFactory::createFlyingObstacle(creationArgs& args){
  std::unique_ptr<Entity> ent_ptr = std::make_unique<FlyingObstacle>(args.x, args.y, args.health, args.damage,
  args.speed, args.width, args.height, args.texture);
  //Flying obstacles have no worth
  ent_ptr->setWorth(0);
  return ent_ptr;
}

std::unique_ptr<Entity> EntityFactory::createEnemyShooter(creationArgs& args){
  std::unique_ptr<Entity> ent_ptr = std::make_unique<EnemyShooter>(args.x, args.y, args.health, args.damage,
  args.speed, args.width, args.height, args.texture);
  int worth = entitiesJson["EnemyShooter"]["worth"];
  ent_ptr->setWorth(worth);
  return ent_ptr;
}

std::unique_ptr<Entity> EntityFactory::createSaucerBoss(creationArgs& args){
  std::unique_ptr<Entity> ent_ptr = std::make_unique<SaucerBoss>(args.x, args.y, args.health, args.damage,
  args.speed, args.width, args.height, args.texture);
  int worth = entitiesJson["SaucerBoss"]["worth"];
  ent_ptr->setWorth(worth);
  return ent_ptr;
}

std::unique_ptr<Entity> EntityFactory::createShooterBoss(creationArgs& args){
  std::unique_ptr<Entity> ent_ptr = std::make_unique<ShooterBoss>(args.x, args.y, args.health, args.damage,
  args.speed, args.width, args.height, args.texture);
  int worth = entitiesJson["ShooterBoss"]["worth"];
  ent_ptr->setWorth(worth);
  return ent_ptr;
}

std::unique_ptr<Entity> EntityFactory::createCrystalBoss(creationArgs& args){
  std::unique_ptr<Entity> ent_ptr = std::make_unique<CrystalBoss>(args.x, args.y, args.health, args.damage,
  args.speed, args.width, args.height, args.texture);
  int worth = entitiesJson["CrystalBoss"]["worth"];
  ent_ptr->setWorth(worth);
  return ent_ptr;
}


}
