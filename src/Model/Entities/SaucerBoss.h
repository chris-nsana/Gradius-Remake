#ifndef SAUCERBOSS_H_
#define SAUCERBOSS_H_
#include <utility>
#include "Enemy.h"

namespace Model{

class SaucerBoss : public Enemy{
public:

  SaucerBoss(float x, float y, float health, float damage, float speed, float width, float height, string texture);

  ~SaucerBoss();

  virtual void update();

  virtual void move();

private:

  //Boolean to determine if the Boss should move forward
  bool moveForward;
  //Counter to countdown when to spawn smaller FlyingSaucer enemies.
  int  spawnTime;

};

}



#endif /* SAUCERBOSS_H_ */
