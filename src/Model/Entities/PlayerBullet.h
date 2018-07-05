#ifndef PLAYERBULLET_H_
#define PLAYERBULLET_H_
#include "Friendly.h"

namespace Model{


class PlayerBullet : public Friendly{
public:

	PlayerBullet(float x, float y, float health, float damage, float width, float height);

	virtual ~PlayerBullet();

	void move();

};

}





#endif /* PLAYERBULLET_H_ */
