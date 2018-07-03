#ifndef ENTITYFACTORY_H_
#define ENTITYFACTORY_H_
#include <memory>
#include <string>
#include <map>
#include <Utilities/json.hpp>
namespace Model{

class EntityFactory{

  //Struct to convienently pass all the needed arguments to the creation methods.
  struct creationArgs{
    float x;
    float y;
    float health;
    float damage;
    float width;
    float height;
    int type;
  };

public:

  EntityFactory();

  ~EntityFactory();

  std::shared_ptr<Entity> create(std::string entity_type);

private:

  std::shared_ptr<Entity> createPlayerShip(creationArgs& args);

  std::shared_ptr<Entity> createPlayerBullet(creationArgs& args);

  std::shared_ptr<Entity> createBorder(creationArgs& args);

  std::shared_ptr<Entity> createBackground(creationArgs& args);

  using creationMethod = std::shared_ptr<Entity> (EntityFactory::*)(creationArgs&)
  std::map<std::string, creationMethod> creationMap;
  nlohmann::json entitiesJson;

};
}



















#endif /* ENTITYFACTORY_H_ */
