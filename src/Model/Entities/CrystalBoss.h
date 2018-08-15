#ifndef CRYSTALBOSS_H_
#define CRYSTALBOSS_H_
#include <utility>
#include "Enemy.h"

namespace Model{

class CrystalBoss : public Enemy{
public:

  CrystalBoss(float x, float y, float health, float damage, float speed, float width, float height, string texture);

  ~CrystalBoss();

  virtual void update();

  virtual void move();

private:

  int shootingTime;


};

}



#endif /* CRYSTALBOSS_H_ */
