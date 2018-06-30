#ifndef PLAYERBULLET_H_
#define PLAYERBULLET_H_
#include "DynamicEntity.h"

class PlayerBullet : public DynamicEntity{
public:

	PlayerBullet(float x, float y);

	virtual ~PlayerBullet();

	void move();

private:
	float originX;
	float originY;

};





#endif /* PLAYERBULLET_H_ */
