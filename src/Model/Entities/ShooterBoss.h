#ifndef SHOOTERBOSS_H_
#define SHOOTERBOSS_H_
#include <utility>
#include "Enemy.h"

namespace Model{

class ShooterBoss : public Enemy{
public:

  ShooterBoss(float x, float y, float health, float damage, float speed, float width, float height, string texture);

  ~ShooterBoss();

  virtual void update();

  virtual void move();

private:

  bool moveUpward;
  int  spawnTime;
  int  shootingTime;

};

}



#endif /* SHOOTERBOSS_H_ */
