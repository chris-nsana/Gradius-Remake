#ifndef ENEMYSHOOTER_H_
#define ENEMYSHOOTER_H_
#include <utility>
#include "Enemy.h"

namespace Model{

class EnemyShooter : public Enemy{
public:

  EnemyShooter(float x, float y, float health, float damage, float speed, float width, float height, string texture);

  ~EnemyShooter();

  virtual void update();

  virtual void move();

};

}



#endif /* ENEMYSHOOTER_H_ */
