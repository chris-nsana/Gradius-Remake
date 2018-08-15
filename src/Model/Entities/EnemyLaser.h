#ifndef ENEMYLASER_H_
#define ENEMYLASER_H_
#include <utility>
#include "Enemy.h"

namespace Model{

class EnemyLaser : public Enemy{
public:

  EnemyLaser(float x, float y, float health, float damage, float speed, float width, float height, string texture);

  ~EnemyLaser();

  virtual void update();

  virtual void move();

private:

  int lifeTime;

};

}



#endif /* ENEMYLASER_H_ */
