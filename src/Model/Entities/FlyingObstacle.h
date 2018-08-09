#ifndef FLYINGOBSTACLE_H_
#define FLYINGOBSTACLE_H_
#include <utility>
#include "Enemy.h"

namespace Model{

class FlyingObstacle : public Enemy{
public:

  FlyingObstacle(float x, float y, float health, float damage, float speed, float width, float height, string texture);

  ~FlyingObstacle();

  virtual void update();

  virtual void move();

private:

};

}



#endif /* FLYINGOBSTACLE_H_ */
