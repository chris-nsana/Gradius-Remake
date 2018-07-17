#ifndef PLAYER_H_
#define PLAYER_H_
#include "Friendly.h"

namespace Model{

class Player : public Friendly{

public:

	Player(float x, float y, float health, float damage, float speed, float width, float height, string texture);

	~Player();

	/**
	*@brief A PlayerShip object has no specific behavior for every tick.
	*/
	void virtual update();

	/**
	*@brief Method that shoots a bullet from this PlayerShip's location.
	*/
	void virtual fire();

	/**
	*@brief A PlayerShip object has no inherent movement pattern, the movement is decided by the Controller.
	*/
	void virtual move();

};

}

#endif /* PLAYER_H_ */
