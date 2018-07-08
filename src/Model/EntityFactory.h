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

  using creationMethod = std::unique_ptr<Entity> (EntityFactory::*)(creationArgs&);
  std::map<std::string, creationMethod> creationMap;
  nlohmann::json entitiesJson;

};
}



















#endif /* ENTITYFACTORY_H_ */
