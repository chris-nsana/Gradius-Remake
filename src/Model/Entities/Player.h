#ifndef PLAYER_H_
#define PLAYER_H_
#include "DynamicEntity.h"


class Player : public DynamicEntity{
	
public:
	
	Player(float x, float y);
	
	~Player();

	void virtual move();

};

#endif /* PLAYER_H_ */


