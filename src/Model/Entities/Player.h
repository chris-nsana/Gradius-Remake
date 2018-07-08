#ifndef PLAYER_H_
#define PLAYER_H_
#include "Friendly.h"

namespace Model{

class Player : public Friendly{

public:

	Player(float x, float y, float health, float damage, float width, float height, string texture);

	~Player();

	void virtual update();

	void virtual fire();

	void virtual move();

};

}

#endif /* PLAYER_H_ */
