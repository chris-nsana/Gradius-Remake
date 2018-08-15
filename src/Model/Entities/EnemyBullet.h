#ifndef ENEMYBULLET_H_
#define ENEMYBULLET_H_
#include <utility>
#include "Enemy.h"

namespace Model{

class EnemyBullet : public Enemy{
public:

  EnemyBullet(float x, float y, float health, float damage, float speed, float width, float height, string texture);

  ~EnemyBullet();

  virtual void update();

  virtual void move();

};

}



#endif /* ENEMYBULLET_H_ */
