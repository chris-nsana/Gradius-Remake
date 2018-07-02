#ifndef ENEMY_H_
#define ENEMY_H_
#include "Entity.h"

namespace Model{

class Enemy : public Enemy{
	//These constructors are not to be called outside the class hierarchy.
	protected:

		Enemy();

		Enemy(float x, float y, float health, float damage, float width, float height, int type);

	public:
		//Public destructor for proper use of smart pointers.
		virtual ~Enemy();

		virtual bool isNeutral() const override;

		virtual void onCollisionReact(Neutral& other) override;

		virtual void onCollisionReact(Friendly& other) override;

		virtual void onCollisionReact(Enemy& other) override;

		virtual void setBlocked()=0;

};
}




#endif /* ENEMY_H_ */
