#ifndef PLAYER_H_
#define PLAYER_H_
#include "Friendly.h"

namespace Model{

class Player : public Friendly{
	
public:
	
	Player(float x, float y);
	
	~Player();

	void virtual move();

};

}

#endif /* PLAYER_H_ */


