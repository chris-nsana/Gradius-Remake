#ifndef ENEMYGRUNT_H_
#define ENEMYGRUNT_H_
#include <utility>
#include "Enemy.h"

namespace Model{

class EnemyGrunt : public Enemy{
public:

  EnemyGrunt(float x, float y, float health, float damage, float speed, float width, float height, string texture);

  ~EnemyGrunt();

  virtual void takeDamage(float amount, bool enemy) override;

  virtual void update();

  virtual void move();

private:

  static std::pair<float, float> swarmPoint;
};

}



#endif /* ENEMYGRUNT_H_ */
