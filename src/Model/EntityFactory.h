#ifndef ENTITYFACTORY_H_
#define ENTITYFACTORY_H_
#include <memory>
#include <string>
#include <map>
#include <Utilities/json.hpp>
namespace Model{

class Entity;

class EntityFactory{

  //Struct to convienently pass all the needed arguments to the creation methods.
  struct creationArgs{
    float x;
    float y;
    float health;
    float speed;
    float damage;
    float width;
    float height;
    std::string texture;
  };

public:

  EntityFactory(std::string entitiesFile);

  ~EntityFactory();

  std::unique_ptr<Entity> create(std::string entity_type);

private:

  std::unique_ptr<Entity> createPlayerShip(creationArgs& args);

  std::unique_ptr<Entity> createPlayerBullet(creationArgs& args);

  std::unique_ptr<Entity> createBorder(creationArgs& args);

  std::unique_ptr<Entity> createBackground(creationArgs& args);

  std::unique_ptr<Entity> createEnemyBullet(creationArgs& args);

  std::unique_ptr<Entity> createEnemyLaser(creationArgs& args);

  std::unique_ptr<Entity> createEnemyGrunt(creationArgs& args);

  std::unique_ptr<Entity> createFlyingSaucer(creationArgs& args);

  std::unique_ptr<Entity> createFlyingObstacle(creationArgs& args);

  std::unique_ptr<Entity> createEnemyShooter(creationArgs& args);

  std::unique_ptr<Entity> createSaucerBoss(creationArgs& args);

  std::unique_ptr<Entity> createShooterBoss(creationArgs& args);

  std::unique_ptr<Entity> createCrystalBoss(creationArgs& args);
  
  int readWorth(std::string type) const;

  using creationMethod = std::unique_ptr<Entity> (EntityFactory::*)(creationArgs&);
  std::map<std::string, creationMethod> creationMap;
  nlohmann::json entitiesJson;

};
}



















#endif /* ENTITYFACTORY_H_ */
