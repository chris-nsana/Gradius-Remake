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
	virtual void update();

	/**
	*@brief Method that shoots a bullet from this PlayerShip's location.
	*/
	virtual void fire();

	virtual void takeDamage(float amount, bool enemy);


	/**
	*@brief A PlayerShip object has no inherent movement pattern, the movement is decided by the Controller.
	*/
	virtual void move();

	/**
	*@brief Move left for the duration of a game tick.
	*/
	void moveLeft();

	/**
	*@brief Move right for the duration of a game tick.
	*/
	void moveRight();

	/**
	*@brief Move up for the duration of a game tick.
	*/
	void moveUp();

	/**
	*@brief Move down for the duration of a game tick.
	*/
	void moveDown();

private:

	int gunJammed;

};

}

#endif /* PLAYER_H_ */
