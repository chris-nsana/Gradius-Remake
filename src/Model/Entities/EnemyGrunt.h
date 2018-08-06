#ifndef ENEMYGRUNT_H_
#define ENEMYGRUNT_H_
#include "Enemy.h"

namespace Model{

class EnemyGrunt : public Enemy{
public:

  EnemyGrunt(float x, float y, float health, float damage, float speed, float width, float height, string texture);

  ~EnemyGrunt();

  virtual void update();

  virtual void move();
};

}



#endif /* ENEMYGRUNT_H_ */
