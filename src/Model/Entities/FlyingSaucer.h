#ifndef FLYINGSAUCER_H_
#define FLYINGSAUCER_H_
#include <utility>
#include "Enemy.h"

namespace Model{

class FlyingSaucer : public Enemy{
public:

  FlyingSaucer(float x, float y, float health, float damage, float speed, float width, float height, string texture);

  ~FlyingSaucer();

  virtual void update();

  virtual void move();

private:

  bool moveUpward;

};

}



#endif /* FLYINGSAUCER_H_ */
