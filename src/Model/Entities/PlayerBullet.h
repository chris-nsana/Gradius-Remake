#ifndef PLAYERBULLET_H_
#define PLAYERBULLET_H_
#include "Friendly.h"

namespace Model{


class PlayerBullet : public Friendly{
public:

	PlayerBullet(float x, float y, float health, float damage, float speed, float width, float height, string texture);

	virtual ~PlayerBullet();

	void move() override;

	void update();

	void fire();

	void setShooterID(int id);

	int getShooterID() const;

private:
	int shooterID;

};

}





#endif /* PLAYERBULLET_H_ */
