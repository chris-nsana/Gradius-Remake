#ifndef PLAYERBULLET_H_
#define PLAYERBULLET_H_
#include "Friendly.h"

namespace Model{


class PlayerBullet : public Friendly.h{
public:

	PlayerBullet(float x, float y);

	virtual ~PlayerBullet();

	void move();

private:
	float originX;
	float originY;

};

}





#endif /* PLAYERBULLET_H_ */
